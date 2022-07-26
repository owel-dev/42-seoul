import { ConsoleLogger, Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Server, Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { User } from 'src/users/entities/user.entity';
import { UsersService } from 'src/users/users.service';
import { Repository } from 'typeorm';
import { Channel, ChatUser } from './chat';

const uuid = require('uuid');

@Injectable()
export class ChatService {
  constructor(
    private readonly authService: AuthService,
    private readonly userService: UsersService,
    @InjectRepository(User)
    private userRepository: Repository<User>,
  ) {}

  static channels = new Map([['0', new Channel()]]);
  static users: ChatUser[] = [];

  async handleConnection(socket: Socket, server: Server) {
    console.log(`Chat: New client connected: ${socket.id}`);
    const token = socket.handshake.query.token as string;
    const clientNick = await this.authService.getUserNickByToken(token);
    const client = await this.userRepository.findOneBy({
      nickname: clientNick,
    });
    // if (ChatService.users.some((user) => user.intraId === client.intra_id)) {
    //   return;
    // }
    ChatService.users.push(new ChatUser(client.intra_id, socket));
    socket.join(client.intra_id);
    this.joinChannel(socket, { channelId: '0' }, server);
  }

  async handleDisconnect(socket: Socket, server: Server) {
    console.log(`Chat: client disconnected: ${socket.id}`);
    const user = ChatService.users.find((user) => user.socket.id === socket.id);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    const prevChannel = ChatService.channels.get(user.curChannel);
    prevChannel.players = prevChannel.players.filter(
      (elem) => elem !== findUser.intra_id,
    );
    prevChannel.muteList = prevChannel.muteList.filter(
      (elem) => elem !== findUser.intra_id,
    );
    ChatService.users = ChatService.users.filter(
      (user) => user.socket.id !== socket.id,
    );
  }

  async sendDirectMessage(client: Socket, data: any, server: Server) {
    console.log(`sendDirectMessage: ${client}, ${data}`);
    if (!this.userService.isBan(data.nickName, [])) {
      const sendTo = await this.userRepository.findOneBy({
        nickname: data.nickName,
      });
      client.join(sendTo.intra_id);
      server.to(sendTo.intra_id).emit('message', {
        nickName: data.nickName,
        message: data.message,
        isDM: true,
      });
      client.leave(sendTo.intra_id);
    }
  }

  async sendChannelMessage(client: Socket, data: any, server: Server) {
    console.log(`sendChannelMessage: ${client.id}`, data);

    const user = ChatService.users.find((user) => user.socket.id === client.id);
    server.to(user.curChannel).emit('message', {
      nickName: data.nickName,
      message: data.message,
      isDM: false,
    });
  }

  async createChannel(client: Socket, server: Server) {
    console.log(`createChannel`);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    const newChannelId = uuid.v4();
    ChatService.channels.set(newChannelId, new Channel());
    this.joinChannel(client, { channelId: newChannelId }, server);
  }

  async joinChannel(client: Socket, data: any, server: Server) {
    console.log(`joinChannel: ${client.id}, ${data}`);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    if (user.curChannel !== '') {
      this.leaveChannel(client, server);
    }
    user.curChannel = data.channelId;
    ChatService.channels.get(data.channelId).players.push(findUser.intra_id);
    console.log('channel:', ChatService.channels.get(data.channelId).players);
    client.join(data.channelId);
    this.sendUserList(client, server);
  }

  async leaveChannel(client: Socket, server: Server) {
    console.log(`leaveChannel: ${client.id}`);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    const prevChannel = ChatService.channels.get(user.curChannel);
    prevChannel.players = prevChannel.players.filter(
      (elem) => elem !== findUser.intra_id,
    );
    prevChannel.muteList = prevChannel.muteList.filter(
      (elem) => elem !== findUser.intra_id,
    );
    client.leave(user.curChannel);
    server
      .to(user.curChannel)
      .emit('user-list', this.getChannelUserList(user.curChannel));
  }

  async getChannelUserList(curChannel: string): Promise<string[]> {
    console.log('getChannelUserList');
    const userList = await Promise.all(
      ChatService.channels.get(curChannel).players.map(async (user) => {
        const findUser = await this.userRepository.findOneBy({
          intra_id: user,
        });
        return findUser.nickname;
      }),
    );
    console.log('user-list:', userList);
    return userList;
  }

  async sendUserList(client: Socket, server: Server) {
    console.log(`sendUserList: ${client.id}`);
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    server
      .to(curChannel)
      .emit('user-list', await this.getChannelUserList(curChannel));
  }

  async muteUser(client: Socket, data: any, server: Server) {
    console.log('muteUser');
    // const userClient = ChatService.users.find(
    //   (user) => user.socket.id === client.id,
    // );
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    const findUser = await this.userRepository.findOneBy({
      nickname: data.nickName,
    });
    const userList = await this.getChannelUserList(curChannel);
    if (userList.includes(data.nickName)) {
      ChatService.channels.get(curChannel).muteList.push(data.nickName);
      ChatService.users
        .find((user) => user.intraId === findUser.intra_id)
        .socket.leave(curChannel);
    }
    console.log(
      `Channel ${curChannel} mute list:`,
      ChatService.channels.get(curChannel).muteList,
    );
  }

  async unmuteUser(client: Socket, data: any, server: Server) {
    console.log('unmuteUser');
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    const findUser = await this.userRepository.findOneBy({
      nickname: data.nickName,
    });
    const muteList = ChatService.channels.get(curChannel).muteList;
    muteList.filter((user) => user !== data.nickName);
    ChatService.users
      .find((user) => user.intraId === findUser.intra_id)
      .socket.join(curChannel);
    console.log(
      `Channel ${curChannel} mute list:`,
      ChatService.channels.get(curChannel).muteList,
    );
  }
}
