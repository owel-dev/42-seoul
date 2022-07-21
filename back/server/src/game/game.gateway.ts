import {
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameService } from './game.service';

@WebSocketGateway({
  cors: {
    origin: '*',
  },
})

export class GameGateway implements OnGatewayConnection, OnGatewayDisconnect, OnGatewayInit {
  @WebSocketServer()
  server: Server;
  constructor(
    private readonly gameService: GameService,
  ) { }

  afterInit() {
    this.gameService.setGameData(this.server);
  }

  handleConnection(socket: Socket) {
    this.gameService.handleConnection(socket);
  }

  handleDisconnect(socket: Socket) {
    this.gameService.handleDisconnect(socket);
  }

  @SubscribeMessage('match-request')
  matchRequest(socket: Socket, data: any): void {
    this.gameService.matchRequest(socket, data);
  }

  @SubscribeMessage('spectate-request')
  spectateRequest(socket: Socket, data: any): void {
    this.gameService.spectateRequest(socket, data);
  }

  @SubscribeMessage('gamelist-request')
  gamelistRequest(): any {
    return this.gameService.gamelistRequest();
  }

  @SubscribeMessage('change-password')
  changePassword(socket: Socket, data: any): any {
    return this.gameService.changePassword(data);
  }

  @SubscribeMessage('submit-password')
  submitPassword(socket: Socket, data: any): boolean {
    return this.gameService.submitPassword(data);
  }

  @SubscribeMessage('get-ping')
  getPing(soket: Socket) {
    return true;
  }

}
