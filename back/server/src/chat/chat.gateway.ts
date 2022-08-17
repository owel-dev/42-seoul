import {
  ConnectedSocket,
  MessageBody,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { ChatService } from './chat.service';

@WebSocketGateway({
  cors: {
    origin: '*',
  },
})
export class ChatGateway {
  constructor(private readonly chatService: ChatService) {}

  @WebSocketServer()
  server: Server;

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

  @SubscribeMessage('set-admin')
  addAdmin(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.setAdmin(client, data, this.server);
  }

  @SubscribeMessage('cancel-admin')
  cancelAdmin(@ConnectedSocket() client: Socket, @MessageBody() data: any) {
    return this.chatService.cancelAdmin(client, data, this.server);
  }

  @SubscribeMessage('friend-start')
  updateFriendList(
    @ConnectedSocket() client: Socket,
    @MessageBody() data: any,
  ) {
    return this.chatService.updateFriendList(client, data, this.server);
  }

  @SubscribeMessage('logout')
  logout(@ConnectedSocket() client: Socket) {
    return this.chatService.logout(client);
  }
}
