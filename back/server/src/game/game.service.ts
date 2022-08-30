import { Injectable, NotFoundException, Param } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Server, Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatService } from 'src/chat/chat.service';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { GameManager } from './game-manager';
import { MatchManager } from './match-manager';

@Injectable()
export class GameService {
  constructor(
    @InjectRepository(User)
    private userRepository: Repository<User>,
    private chatService: ChatService,
    private matchManager: MatchManager,
    private gameManager: GameManager,
  ) {}

  // static matchManager = new MatchManager();
  // static gameManager = new GameManager();

  // async handleConnection(socket: Socket) {
  // console.log(`New client connected: ${socket.id}`);

  // // console.log("token", token);
  // const token = socket.handshake.query.accessToken as string;
  // const nickName = await this.authService.getUserNickByToken(token);
  // if (nickName === undefined) return;
  // console.log(`nick: ${nickName}, socket: ${socket.id}`);

  // await this.userRepository.update(
  //     { nickname: nickName },
  //     { socket_id: socket.id },
  // );
  // const userRow = await this.userRepository.findOneBy({ nickname: nickName });
  // if (userRow === undefined) throw new NotFoundException();

  // if (userRow.status == 'spectate') socket.join(userRow.channel_id);
  // else if (userRow.status == 'gaming') {
  //     // console.log('channel_id: ', userRow.channel_id);
  //     // console.log('socket_id: ', socket.id);
  //     this.gameManager.changeSocket(userRow.channel_id, nickName, socket);
  // }
  // }

  // async handleDisconnect(socket: Socket) {
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
  // }

  async matchRequest(
    socket: Socket,
    data: any,
    server: Server,
    togetherAccept: Boolean,
  ): Promise<void> {
    ('in matchRequest');
    let remakeMode = data.gameMode + ' ' + data.password.replace(' ', '');
    if (data.oppNickName && !togetherAccept)
      remakeMode += ' ' + data.oppNickName;
    else if (data.oppNickName && togetherAccept)
      remakeMode += ' ' + data.nickName;
    // console.log('@@remakeMode=', remakeMode);
    this.matchManager.addUser(
      socket,
      remakeMode,
      data.nickName,
      data.password,
      data.gameMode,
    );
    if (this.matchManager.isTwoUser(remakeMode)) {
      // console.log('isTwoUser');
      this.gameManager.addNewGame(
        this.matchManager.getMatchData(remakeMode),
        server,
      );
      this.matchManager.clearQueueMode(remakeMode);
    }
  }

  async matchCancel(
    socket: Socket,
    nickName: any,
    server: Server,
  ): Promise<void> {
    this.matchManager.clearQueueSocket(socket.id);
    if (nickName) {
      const userRow = await this.userRepository.findOne({
        where: { nickname: nickName },
      });
      if (!userRow) throw new NotFoundException();
      //   console.log(`match-cancel to ${userRow.socket_id}`);
      server.to(userRow.socket_id).emit('match-cancel');
    }
  }

  async spectateRequest(
    socket: Socket,
    data: any,
    server: Server,
  ): Promise<void> {
    this.userRepository.update(
      { socket_id: socket.id },
      { channel_id: data.channelId, status: 'spectate' },
    );
    socket.join(data.channelId);
    this.chatService.joinChannel(socket, data, server);
  }

  gamelistRequest(): GetChannelDto[] {
    return this.gameManager.getChannelList();
  }

  changePassword(data: any, server: Server): void {
    this.gameManager.changePassword(data.channelId, data.password, server);
  }

  spectatePassword(data: any): boolean {
    if (!data.password || !data.channelId) return false;
    if (
      data.password == this.gameManager.getPassword(data.channelId).password
    ) {
      return true;
    } else {
      return false;
    }
  }

  async clientLeave(socket: Socket, server: Server) {
    // console.log('clientleave');

    // 만약 플레이어면 stopsignal 호출.

    const user = await this.userRepository.findOneBy({ socket_id: socket.id });
    // console.log(`socket.id: ${socket.id}, user: ${user}`);
    if (this.gameManager.isPlayer(user)) {
      this.gameManager.stopGame(user.channel_id, user.nickname);
    }
    const prevChannel = user.channel_id;
    // if (user.status === 'spectate') {
    //     socket.leave(user.channel_id);
    // }

    if (user.status !== 'offline') {
      await this.chatService.joinChannel(socket, { channelId: '0' }, server);
      user.status = 'online';
    }
    user.channel_id = '0';
    await this.userRepository.save(user);

    const findChannelUser = await this.userRepository.find({
      where: { channel_id: prevChannel },
    });

    if (findChannelUser.length === 0) {
      // console.log('closegame');
      this.gameManager.closeGame(prevChannel);
      server.emit('gamelist-update');
    }
  }

  gamePlayerData(socket: Socket, channelId: string) {
    const gameMode = this.gameManager.getMode(channelId);
    const { firstPlayer, secondPlayer } = this.gameManager.getPlayer(channelId);
    // console.log(`gameMode: ${gameMode} ${firstPlayer} ${secondPlayer}`);
    if (
      gameMode !== undefined &&
      firstPlayer !== undefined &&
      secondPlayer !== undefined
    ) {
      return {
        gameMode: gameMode,
        firstPlayer: firstPlayer,
        secondPlayer: secondPlayer,
      };
    }
    return undefined;
  }

  async togetherRequest(
    socket: Socket,
    data: any,
    server: Server,
  ): Promise<void> {
    // console.log('in together-request: ', data);
    const userRow = await this.userRepository.findOne({
      where: { nickname: data.oppNickName },
    });
    if (!userRow) throw new NotFoundException();
    // console.log('together: ', server.sockets.adapter.rooms);
    server.to(userRow.socket_id).emit('together-request', data);
    this.matchRequest(socket, data, server, false);
    // socket.emit('together-request', { nickName: , gameMode: , });
    // let remakeMode = data.gameMode + ' ' + data.password.replace(' ', '');
    // this.matchManager.addUser(socket, remakeMode, data.nickName, data.password, data.gameMode);
  }

  async togetherResponse(socket: Socket, response: any, server: Server) {
    const temp = response.data.nickName;
    response.data.nickName = response.data.oppNickName;
    response.data.oppNickName = temp;

    if (response.status === true) {
      this.matchRequest(socket, response.data, server, true);
      return;
    } else {
      const userFind = await this.userRepository.findOneBy({
        nickname: response.data.oppNickName,
      });
      if (!userFind) throw new NotFoundException();
      this.matchManager.clearQueueSocket(userFind.socket_id);
      server.to(userFind.socket_id).emit('match-cancel');
    }

    let remakeMode =
      response.data.gameMode + ' ' + response.data.password.replace(' ', '');
    this.matchManager.clearQueueMode(remakeMode);
  }
}
