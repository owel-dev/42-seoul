import { Socket } from 'socket.io';
import { User } from 'src/users/entities/user.entity';

export class ChatUser {
  intraId: string;
  socket: Socket;
  curChannel: string;
  isConenected: boolean;

  constructor(intraId: string, socket: Socket) {
    this.intraId = intraId;
    this.socket = socket;
    this.curChannel = '';
    this.isConenected = true;
  }
}

export class Channel {
  players: string[] = [];
  muteList: string[] = [];
  admin = '';
}

export class ResChatUser {
  nickName: string;
  admin: boolean;
}
