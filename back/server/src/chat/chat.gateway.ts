import { Query, UseGuards } from '@nestjs/common';
import {
  ConnectedSocket,
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { Token } from 'src/auth/auth.decorator';
import { AuthGuard } from 'src/auth/auth.guard';
import { ChatService } from './chat.service';

@WebSocketGateway({
  cors: {
    origin: '*',
  },
})
export class ChatGateway
  implements OnGatewayConnection, OnGatewayDisconnect, OnGatewayInit
{
  constructor(private readonly chatService: ChatService) {}

  @WebSocketServer()
  server: Server;

  afterInit() {}

  handleConnection(socket: Socket) {
    this.chatService.handleConnection(socket, this.server);
  }

  handleDisconnect(socket: Socket) {
    this.chatService.handleDisconnect(socket, this.server);
  }

  @SubscribeMessage('create-channel')
  createChannel(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.createChannel(client, data.channelId, this.server);
  }

  @SubscribeMessage('join-channel')
  joinChannel(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.joinChannel(client, data, this.server);
  }

  @SubscribeMessage('direct-message')
  directMessage(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.sendDirectMessage(client, data, this.server);
  }

  @SubscribeMessage('message')
  channelMessage(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.sendChannelMessage(client, data, this.server);
  }

  @SubscribeMessage('user-list')
  getUserList(@ConnectedSocket() client: Socket) {
    return this.chatService.sendUserList(client, this.server);
  }

  @SubscribeMessage('mute')
  muteUser(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.muteUser(client, data, this.server);
  }

  @SubscribeMessage('admin')
  setAdmin(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.setAdmin(client, data, this.server);
  }

  @SubscribeMessage('friend-start')
  updateFriendList(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: any,
  ) {
    return this.chatService.updateFriendList(client, data, this.server);
  }
}
