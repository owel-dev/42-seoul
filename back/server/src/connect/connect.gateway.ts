import {
  OnGatewayConnection,
  OnGatewayDisconnect,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { ApiTags } from '@nestjs/swagger';
import { ConnectService } from './connect.service';

@WebSocketGateway({
  cors: {
    origin: '*',
  },
})
export class ConnectGateway implements OnGatewayConnection, OnGatewayDisconnect {
  constructor(private connectService: ConnectService) { }

  @WebSocketServer()
  server: Server;

  async handleConnection(socket: Socket) {
    this.connectService.handleConnection(socket, this.server);
  }

  async handleDisconnect(socket: Socket) {
    this.connectService.handleDisconnect(socket, this.server);
  }
}
