import { forwardRef, Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Server, Socket } from 'socket.io';
import { AuthService } from 'src/auth/auth.service';
import { Ban } from 'src/ban/entities/ban.entity';
import { ResFriendDto } from 'src/friend/dto/res-friend.dto';
import { Friend } from 'src/friend/entities/friend.entity';
import { User } from 'src/users/entities/user.entity';
import { UsersService } from 'src/users/users.service';
import { Repository } from 'typeorm';
import { ResChatUser } from './chat';
import { Channel, ChatUser } from './chat';

@Injectable()
export class ChatService {
  constructor(
    private readonly authService: AuthService,
    @Inject(forwardRef(() => UsersService))
    private readonly userService: UsersService,
    @InjectRepository(User)
    private userRepository: Repository<User>,
    @InjectRepository(Friend)
    private friendRepository: Repository<Friend>,
    @InjectRepository(Ban)
    private banRepository: Repository<Ban>,
  ) {}

  static channels = new Map([['0', new Channel()]]);
  static users: ChatUser[] = [];

  // async handleConnection(socket: Socket, server: Server) {
  // console.log(`Chat: New client connected: ${socket.id}`);
  // const token = socket.handshake.query.accessToken as string;
  // const clientNick = await this.authService.getUserNickByToken(token);
  // if (!clientNick) return;
  // const client = await this.userRepository.findOneBy({
  //   nickname: clientNick,
  // });
  // const user = ChatService.users.find(
  //   (user) => user.intraId === client.intra_id,
  // );
  // ChatService.users.push(new ChatUser(client.intra_id, socket));
  // socket.join(client.intra_id);
  // client.status = 'online';
  // client.channel_id = '0';
  // this.userRepository.save(client);
  // await this.joinChannel(socket, { channelId: '0' }, server);
  // }

  // async handleDisconnect(socket: Socket, server: Server) {
  //   // console.log(`Chat: client disconnected: ${socket.id}`);
  //   const user = ChatService.users.find((user) => user.socket.id === socket.id);
  //   if (!user) {
  //     return;
  //   }
  //   const findUser = await this.userRepository.findOneBy({
  //     intra_id: user.intraId,
  //   });
  //   findUser.status = 'offline';
  //   this.userRepository.save(findUser);
  //   this.leaveChannel(socket, server);
  //   ChatService.users = ChatService.users.filter(
  //     (user) => user.socket.id !== socket.id,
  //   );
  // }

  async sendDirectMessage(client: Socket, data: any, server: Server) {
    // console.log(`sendDirectMessage: ${client.id}`, data);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    if (!user)
      return ;
    const findUser = await this.userRepository.findOne({
      where: {
        intra_id: user.intraId,
      },
    });
    const isBan = await this.banRepository.find({
      relations: ['ban_1', 'ban_2'],
      where: {
        ban_1: { nickname: data.nickName },
        ban_2: { intra_id: user.intraId },
      },
    });

    if (isBan.length === 0) {
      const sendTo = await this.userRepository.findOneBy({
        nickname: data.nickName,
      });
      if (!sendTo)
        return ;
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
    const banRepo = await this.banRepository.find({
      relations: ['ban_1', 'ban_2'],
      where: {
        ban_2: { intra_id: user.intraId },
      },
    });
    const bannerList = banRepo.map((ban) => ban.ban_1.intra_id);
    if (
      !ChatService.channels.get(user.curChannel).muteList.includes(user.intraId)
    ) {
      server.to(user.curChannel).except(bannerList).emit('message', {
        nickName: data.nickName,
        message: data.message,
        isDM: false,
      });
      //   console.log(
      //     `sendMessage to channel ${user.curChannel} from ${data.nickName} "${data.message}"`,
      //   );
    }
  }

  async createChannel(client: Socket, channelId: string, server: Server) {
    // console.log(`createChannel`);
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    ChatService.channels.set(channelId, new Channel());

    await this.joinChannel(client, { channelId: channelId }, server);
    await this.addChannelAdmin(channelId, user.intraId, server);
    ChatService.channels.get(channelId).owner = user.intraId;
  }

  async joinChannel(client: Socket, data: any, server: Server) {
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    // console.log(`@@client.id: ${client.id}`, data);
    // console.log(user);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    if (user.curChannel !== '') {
      await this.leaveChannel(client, server);
    }
    user.curChannel = data.channelId;
    // console.log(`@@channelId: ${data.channelId}`);
    ChatService.channels.get(data.channelId).players.push(findUser.intra_id);
    client.join(data.channelId);
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
    if (prevChannel.adminList.includes(findUser.intra_id))
      await this.removeChannelAdmin(
        user.curChannel,
        user.intraId,
        server,
        true,
      );
    client.leave(user.curChannel);
    if (prevChannel.players.length === 0 && user.curChannel !== '0') {
      ChatService.channels.delete(user.curChannel);
      return;
    }
    server
      .to(user.curChannel)
      .emit('user-list', await this.getChannelUserList(user.curChannel));
  }

  async getChannelUserList(curChannel: string): Promise<ResChatUser[]> {
    // console.log('getChannelUserList');
    // console.log("curChannel=: ", curChannel)
    if (!ChatService.channels.get(curChannel))
      return ;
    const userList = await Promise.all(
      ChatService.channels.get(curChannel)?.players.map(async (user) => {
        const findUser = await this.userRepository.findOneBy({
          intra_id: user,
        });
        const resChatUser = new ResChatUser();
        resChatUser.nickName = findUser.nickname;
        resChatUser.owner =
          ChatService.channels.get(curChannel)?.owner === user;
        resChatUser.admin = ChatService.channels
          .get(curChannel)
          .adminList.includes(user);
        return resChatUser;
      }),
    );
    return userList;
  }

  async sendUserList(client: Socket, server: Server) {
    const curUser = ChatService.users.find(
      (user) => user.socket.id === client.id,
    );
    if (!curUser)
      return ;
    // console.log('curUser=', curUser)
    // console.log("curChannel=: ", curUser.curChannel);
    // console.log(`sendUserList: ${ client.id }`);
    server
      .to(curUser.curChannel)
      .emit('user-list', await this.getChannelUserList(curUser.curChannel));
  }

  async muteUser(client: Socket, data: any, server: Server) {
    // console.log('muteUser');
    const userClient = ChatService.users.find(
      (user) => user.socket.id === client.id,
    );
    const curChannelId = userClient.curChannel;
    const curChannel = ChatService.channels.get(curChannelId);
    const findUser = await this.userRepository.findOneBy({
      nickname: data,
    });
    const userList = await this.getChannelUserList(curChannelId);
    if (userList.some((user) => user.nickName === data)) {
      curChannel.muteList.push(findUser.intra_id);
    }
    setTimeout(() => {
      curChannel.muteList = curChannel.muteList.filter(
        (user) => user !== findUser.intra_id,
      );
    }, 30 * 1000);
  }

  async setAdmin(client: Socket, data: any, server: Server) {
    // console.log(`set admin ${data}`);
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    const userFind = await this.userRepository.findOneBy({
      nickname: data,
    });
    await this.addChannelAdmin(curChannel, userFind.intra_id, server);
  }

  async cancelAdmin(client: Socket, data: any, server: Server) {
    // console.log(`cancel admin ${data}`);
    const curChannel = ChatService.users.find(
      (user) => user.socket.id === client.id,
    ).curChannel;
    const userFind = await this.userRepository.findOneBy({
      nickname: data,
    });
    this.removeChannelAdmin(curChannel, userFind.intra_id, server, false);
  }

  async addChannelAdmin(channelId: string, intraId: string, server: Server) {
    const userFind = await this.userRepository.findOneBy({ intra_id: intraId });
    ChatService.channels.get(channelId).adminList.push(intraId);
    server
      .to(channelId)
      .emit('user-list', await this.getChannelUserList(channelId));
    server.to(channelId).emit('message', {
      nickName: null,
      message: `${userFind.nickname}(을)를 방장으로 임명하였습니다)`,
      isDM: false,
    });
  }

  async removeChannelAdmin(
    channelId: string,
    intraId: string,
    server: Server,
    isMoveChannel: boolean,
  ) {
    const userFind = await this.userRepository.findOneBy({ intra_id: intraId });
    let adminList = ChatService.channels.get(channelId).adminList;
    for (let i = 0; i < adminList.length; ++i) {
      if (adminList[i] === intraId) adminList.splice(i, 1);
    }
    if (!isMoveChannel) {
      server
        .to(channelId)
        .emit('user-list', await this.getChannelUserList(channelId));
      server.to(channelId).emit('message', {
        nickName: null,
        message: `${userFind.nickname}의 방장 권한을 박탈하였습니다)`,
        isDM: false,
      });
    }
  }

  async updateFriendList(client: Socket, data: any, server: Server) {
    // console.log('updateFriendList');
    const user = ChatService.users.find((user) => user.socket.id === client.id);

    const timeId = setInterval(async () => {
      const friendList = await this.friendRepository.find({
        relations: {
          friend_1: true,
          friend_2: true,
        },
        where: { friend_1: { nickname: data } },
      });
      const resFriendList = friendList.map((friend) => {
        const resFriendDto = new ResFriendDto();
        resFriendDto.nickName = friend.friend_2.nickname;
        resFriendDto.status = friend.friend_2.status;
        resFriendDto.channelId = friend.friend_2.channel_id;
        return resFriendDto;
      });
      client.emit('friend', { friendList: resFriendList });
    }, 1000);
    client.once('friend-end', () => {
      clearTimeout(timeId);
    });
  }

  async logout(client: Socket) {
    // console.log('logout');
    const user = ChatService.users.find((user) => user.socket.id === client.id);
    const findUser = await this.userRepository.findOneBy({
      intra_id: user.intraId,
    });
    // console.log('findUser', findUser);
    if (findUser.enable2fa) {
      // console.log('enable2fa');
      findUser.is_second_auth = false;
      await this.userRepository.save(findUser);
    }
  }
}
