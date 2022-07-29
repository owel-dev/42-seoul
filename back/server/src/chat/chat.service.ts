import {
  ConsoleLogger,
  forwardRef,
  HttpException,
  HttpStatus,
  Inject,
  Injectable,
  NotFoundException,
} from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { WsException } from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { User } from 'src/users/entities/user.entity';
import { UsersService } from 'src/users/users.service';
import { Repository } from 'typeorm';
import { ResChatUser } from './chat';
import { Channel, ChatUser } from './chat';

const uuid = require('uuid');

@Injectable()
export class ChatService {
  constructor(
    private readonly authService: AuthService,
    @Inject(forwardRef(() => UsersService))
    private readonly userService: UsersService,
    @InjectRepository(User)
    private userRepository: Repository<User>,
  ) {}

  static channels = new Map([['0', new Channel()]]);
  static users: ChatUser[] = [];

  async handleConnection(socket: Socket, server: Server) {
    // console.log(`Chat: New client connected: ${socket.id}`);
    const token = socket.handshake.query.token as string;
    const clientNick = await this.authService.getUserNickByToken(token);
    if (!clientNick) return;
    const client = await this.userRepository.findOneBy({
      nickname: clientNick,
    });
    const user = ChatService.users.find(
      (user) => user.intraId === client.intra_id,
    );
    if (user) {
      user.socket = socket;
      user.isConenected = true;
      socket.join(client.intra_id);
      socket.join(user.curChannel);
      socket.join(user.curChannel + '-chat');
      await this.sendUserList(socket, server);
    } else {
      ChatService.users.push(new ChatUser(client.intra_id, socket));
      socket.join(client.intra_id);
      await this.joinChannel(socket, { channelId: '0' }, server);
    }
  }

  async handleDisconnect(socket: Socket, server: Server) {
    // console.log(`Chat: client disconnected: ${socket.id}`);
    const user = ChatService.users.find((user) => user.socket.id === socket.id);
    if (!user) {
      return;
    }
    user.isConenected = false;
    setTimeout(() => {
      if (!user.isConenected) {
        this.leaveChannel(socket, server);
        ChatService.users = ChatService.users.filter(
          (user) => user.socket.id !== socket.id,
        );
      }
    }, 3000);
  }

  async sendDirectMessage(client: Socket, data: any, server: Server) {
    // console.log(`sendDirectMessage: ${client.id}`, data);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    if (!(await this.userService.isBan(data.nickName, []))) {
      const sendTo = await this.userRepository.findOneBy({
        nickname: data.nickName,
      });

      client.join(sendTo.intra_id);
      server.to(sendTo.intra_id).emit('message', {
        nickName: findUser.nickname,
        message: data.message,
        isDM: true,
      });
      //   console.log(
      //     `sendMessage to ${sendTo.intra_id} from ${findUser.nickname} "${data.message}"`,
      //   );
      client.leave(sendTo.intra_id);
    }
  }

  async sendChannelMessage(client: Socket, data: any, server: Server) {
    // console.log(`sendChannelMessage: ${client.id}`, data);

    const user = ChatService.users.find((user) => user.socket.id === client.id);
    server.to(user.curChannel + '-chat').emit('message', {
      nickName: data.nickName,
      message: data.message,
      isDM: false,
    });
    // console.log(
    //   `sendMessage to channel ${user.curChannel} from ${data.nickName} "${data.message}"`,
    // );
  }

  async createChannel(client: Socket, channelId: string, server: Server) {
    // console.log(`createChannel`);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    ChatService.channels.set(channelId, new Channel());
    await this.joinChannel(client, { channelId: channelId }, server);
  }

  async joinChannel(client: Socket, data: any, server: Server) {
    // console.log(`joinChannel: ${client.id}, ${data}`);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    if (user.curChannel !== '') {
      await this.leaveChannel(client, server);
    }
    user.curChannel = data.channelId;
    ChatService.channels.get(data.channelId).players.push(findUser.intra_id);
    if (
      data.channelId !== '0' &&
      ChatService.channels.get(data.channelId).admin === ''
    )
      await this.changeChannelAdmin(data.channelId, findUser.intra_id, server);
    client.join(data.channelId);
    client.join(data.channelId + '-chat');
    await this.sendUserList(client, server);
  }

  async leaveChannel(client: Socket, server: Server) {
    // console.log(`leaveChannel: ${client.id}`);
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
    if (prevChannel.admin === findUser.intra_id)
      await this.changeChannelAdmin(
        user.curChannel,
        prevChannel.players[0],
        server,
      );
    client.leave(user.curChannel);
    client.leave(user.curChannel + '-chat');
    server
      .to(user.curChannel)
      .emit('user-list', await this.getChannelUserList(user.curChannel));
  }

  async getChannelUserList(curChannel: string): Promise<ResChatUser[]> {
    // console.log('getChannelUserList');
    const userList = await Promise.all(
      ChatService.channels.get(curChannel).players.map(async (user) => {
        const findUser = await this.userRepository.findOneBy({
          intra_id: user,
        });
        return {
          nickName: findUser.nickname,
          admin: ChatService.channels.get(curChannel).admin === user,
        };
      }),
    );
    // console.log(`user-list in ${curChannel}`, userList);
    return userList;
  }

  async sendUserList(client: Socket, server: Server) {
    // console.log(`sendUserList: ${client.id}`);
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    server
      .to(curChannel)
      .emit('user-list', await this.getChannelUserList(curChannel));
  }

  async muteUser(client: Socket, data: any, server: Server) {
    // console.log('muteUser');
    const userClient = ChatService.users.find(
      (user) => user.socket.id === client.id,
    );
    const curChannel = userClient.curChannel;
    const findUser = await this.userRepository.findOneBy({
      nickname: data.nickName,
    });
    const userList = await this.getChannelUserList(curChannel);
    if (userList.some((user) => user.nickName === data.nickName)) {
      ChatService.channels.get(curChannel).muteList.push(data.nickName);
      ChatService.users
        .find((user) => user.intraId === findUser.intra_id)
        .socket.leave(curChannel + '-chat');
    }
    // console.log(
    //   `Channel ${curChannel} mute list:`,
    //   ChatService.channels.get(curChannel).muteList,
    // );
    setTimeout(() => {
      ChatService.channels
        .get(curChannel)
        .muteList.filter((user) => user !== data.nickName);
      ChatService.users
        .find((user) => user.intraId === findUser.intra_id)
        .socket.join(curChannel);
    }, 0.1 * 60 * 1000);
    // console.log(
    //   `Channel ${curChannel} mute list:`,
    //   ChatService.channels.get(curChannel).muteList,
    // );
  }

  async setAdmin(client: Socket, data: any, server: Server) {
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    const userFind = await this.userRepository.findOneBy({
      nickname: data.nickName,
    });
    await this.changeChannelAdmin(curChannel, userFind.intra_id, server);
  }

  async changeChannelAdmin(channelId: string, intraId: string, server: Server) {
    const findUser = await this.userRepository.findOneBy({ intra_id: intraId });
    ChatService.channels.get(channelId).admin = intraId;
    server
      .to(channelId)
      .emit('user-list', await this.getChannelUserList(channelId));
    server.to(channelId).emit('admin-changed', findUser.nickname);
  }
}
