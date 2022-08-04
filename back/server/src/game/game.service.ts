import { Injectable, NotFoundException, Param } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { filter } from 'rxjs';
import { Server, Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatService } from 'src/chat/chat.service';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { Game } from './game';
import { GameManager } from './game-manager';
import { MatchManager } from './match-manager';

@Injectable()
export class GameService {
  constructor(
    private authService: AuthService,
    @InjectRepository(User)
    private userRepository: Repository<User>,
    private chatService: ChatService,
    private matchManager: MatchManager,
    private gameManager: GameManager,
  ) {}

  // static matchManager = new MatchManager();
  // static gameManager = new GameManager();

  async handleConnection(socket: Socket) {
    console.log(`New client connected: ${socket.id}`);

    // console.log("token", token);
    const token = socket.handshake.query.token as string;
    const nickName = await this.authService.getUserNickByToken(token);
    if (nickName === undefined) return;
    // console.log('nick: ', nickName);

    const userRow = await this.userRepository.findOneBy({ nickname: nickName });
    if (userRow === undefined) throw new NotFoundException();

    if (userRow.status == 'spectate') socket.join(userRow.channel_id);
    else if (userRow.status == 'gamming') {
      // console.log('channel_id: ', userRow.channel_id);
      // console.log('socket_id: ', socket.id);

      this.gameManager.changeSocket(userRow.channel_id, nickName, socket);
    }

    await this.userRepository.update(
      { nickname: nickName },
      { socket_id: socket.id },
    );
  }

  async checkReconnect(userNick: string) {
    const userRow = await this.userRepository.findOneBy({ nickname: userNick });
    if (userRow === undefined) throw new NotFoundException();
    if (userRow.socket_id == null) {
      // 게임 종료
    }
  }

  async handleDisconnect(socket: Socket) {
    // console.log(`Client Disconnected: ${socket.id}`);
    // const userRow = await this.userRepository.findOneBy({ socket_id: socket.id });
    // if (userRow === undefined)
    //     throw new NotFoundException();
    // console.log("socketId: ", userRow.socket_id);
    // userRow.socket_id = null;
    // await this.userRepository.save(userRow);
    // const userNick = userRow.nickname;
    // setTimeout(() => {
    //     this.checkReconnect(userNick);
    // }, 60 * 1000 * 3);
  }

  async matchRequest(socket: Socket, data: any, server: Server): Promise<void> {
    let remakeMode = data.mode + ' ' + data.password.replace(' ', '');

    this.matchManager.addUser(socket, remakeMode, data.nickName, data.password);
    if (this.matchManager.isTwoUser(remakeMode)) {
      this.gameManager.addNewGame(
        this.matchManager.getMatchData(remakeMode),
        server,
      );
      this.matchManager.clearQueue(remakeMode);
    }
  }

  matchCancel(): void {
    // this.matchManager.clearQueue(data.mode);
  }

  async spectateRequest(
    socket: Socket,
    data: any,
    server: Server,
  ): Promise<void> {
    this.userRepository.update(
      { socket_id: socket.id },
      { status: 'spectate' },
    );
    socket.join(data.channelId);
    this.chatService.joinChannel(socket, data.gameId, server);
  }

  gamelistRequest(): any {
    return this.gameManager.getChannelList();
  }

  changePassword(data: any): void {
    this.gameManager.changePassword(data.channelId, data.password);
  }

  spectatePassword(data: any): boolean {
    //     if (!data.password || !data.channelId)
    //         return false;
    //     games.map((item) => {
    //         if (item.channelId === data.channelId &&
    //             item.password === data.password)
    //             return true;
    //     });
    return false;
    // }
  }

  async clientLeave(socket: Socket, server: Server) {
    console.log('clientleave');
    const user = await this.userRepository.findOneBy({ socket_id: socket.id });
    const prevChannel = user.channel_id;
    if (user.status === 'spectate') {
      socket.leave(user.channel_id);
    }
    user.status = 'online';
    user.channel_id = '0';
    await this.userRepository.save(user);
    const findChannelUser = await this.userRepository.find({
      where: { channel_id: prevChannel },
    });
    console.log(findChannelUser);
    if (findChannelUser.length === 0) {
      this.gameManager.closeGame(prevChannel);
    }
    this.chatService.joinChannel(socket, { channelId: '0' }, server);
  }
}