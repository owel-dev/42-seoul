import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Server, Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { ChatUser } from 'src/chat/chat';
import { ChatService } from 'src/chat/chat.service';
import { GameManager } from 'src/game/game-manager';
import { GameService } from 'src/game/game.service';
import { MatchManager } from 'src/game/match-manager';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';

@Injectable()
export class ConnectService {
  constructor(
    private readonly authService: AuthService,
    private readonly chatService: ChatService,
    private readonly gameService: GameService,
    @InjectRepository(User)
    private readonly userRepository: Repository<User>,
    private readonly gameManager: GameManager,
    private readonly matchManager: MatchManager,
  ) {}

  async handleConnection(socket: Socket, server: Server) {
    // console.log(`New client connected: ${socket.id}`);

    // 소켓 연결한 유저 닉네임 가져오기.
    const token = socket.handshake.query.accessToken as string;
    const clientNick = await this.authService.getUserNickByToken(token);
    if (!clientNick) return;

    // console.log(`nick: ${clientNick}, socket: ${socket.id}`);

    // 닉네임으로 row 가져오기.
    const client = await this.userRepository.findOneBy({
      nickname: clientNick,
    });

    ChatService.users.push(new ChatUser(client.intra_id, socket));

    // socket_id 세팅
    client.socket_id = socket.id;
    // status 세팅
    if (client.status == 'spectate') socket.join(client.channel_id);
    else if (client.status == 'gaming') {
      this.gameManager.changeSocket(client.channel_id, clientNick, socket);
    } else if (client.status == 'offline') {
      client.status = 'online';
      client.channel_id = '0';
    }
    await this.userRepository.save(client);

    // chat user에 추가
    socket.join(client.intra_id);
    await this.chatService.joinChannel(socket, { channelId: '0' }, server);
    socket.emit('connected');
  }

  async handleDisconnect(socket: Socket, server: Server) {
    // console.log(`Chat: client disconnected: ${socket.id}`);
    const user = ChatService.users.find((user) => user.socket.id === socket.id);
    if (!user) {
      return;
    }
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });

    findUser.status = 'offline';
    await this.userRepository.save(findUser);

    await this.chatService.leaveChannel(socket, server);
    if (findUser.channel_id !== '0')
      await this.gameService.clientLeave(socket, server);

    ChatService.users = ChatService.users.filter(
      (user) => user.socket.id !== socket.id,
    );

    this.matchManager.clearQueueSocket(socket.id);
  }
}
