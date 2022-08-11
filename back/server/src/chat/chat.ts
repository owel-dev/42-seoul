import { Socket } from 'socket.io';
import { User } from 'src/users/entities/user.entity';

export class ChatUser {
  intraId: string;
  socket: Socket;
  curChannel: string;

  constructor(intraId: string, socket: Socket) {
    this.intraId = intraId;
    this.socket = socket;
    this.curChannel = '';
  }
}

export class Channel {
  players: string[] = [];
  muteList: string[] = [];
  owner = '';
  adminList: string[] = [];
}

export class ResChatUser {
  nickName: string;
  owner: boolean;
  admin: boolean;
}
