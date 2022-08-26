import {
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
} from '@nestjs/websockets';
import { Server, Socket } from 'socket.io';
import { GameService } from './game.service';
import { ApiTags } from '@nestjs/swagger';

@WebSocketGateway({
  cors: {
    origin: '*',
  },
})
@ApiTags('게임 관련 소켓 API')
export class GameGateway {
  constructor(private readonly gameService: GameService) {}

  @WebSocketServer()
  server: Server;

  // handleConnection(socket: Socket) {
  //   this.gameService.handleConnection(socket);
  // }

  // handleDisconnect(socket: Socket) {
  //   this.gameService.handleDisconnect(socket);
  // }

  @SubscribeMessage('match-request')
  matchRequest(socket: Socket, data: any): void {
    // console.log('match-request');
    this.gameService.matchRequest(socket, data, this.server, false);
  }

  @SubscribeMessage('match-cancel')
  matchCancel(socket: Socket, data: any): void {
    // console.log('match-cancel');
    this.gameService.matchCancel(socket, data, this.server);
  }

  @SubscribeMessage('spectate-request')
  spectateRequest(socket: Socket, data: any): void {
    this.gameService.spectateRequest(socket, data, this.server);
  }

  @SubscribeMessage('gamelist-request')
  gamelistRequest(socket: Socket): any {
    return {
      channelList: this.gameService.gamelistRequest(),
    };
  }

  @SubscribeMessage('change-password')
  changePassword(socket: Socket, data: any): any {
    return this.gameService.changePassword(data, this.server);
  }

  @SubscribeMessage('spectate-password')
  spectatePassword(socket: Socket, data: any): boolean {
    return this.gameService.spectatePassword(data);
  }

  @SubscribeMessage('get-ping')
  getPing(soket: Socket) {
    return true;
  }

  @SubscribeMessage('leave-channel')
  clientLeave(socket: Socket): any {
    //게임 방 목록에서 해당 소켓에 대한 유저를 지우고,
    //만약 더 남은 유저가 없으면 방 폭파
    this.gameService.clientLeave(socket, this.server);
    // console.log()
  }

  @SubscribeMessage('game-player-data')
  gamePlayerData(socket: Socket, channelId: string): any {
    const a = this.gameService.gamePlayerData(socket, channelId);
    // console.log('palyer: ', a);
    return a;
    // console.log();
  }

  @SubscribeMessage('together-request')
  togetherRequest(socket: Socket, data: any): any {
    // console.log('together-request');
    this.gameService.togetherRequest(socket, data, this.server);
  }

  @SubscribeMessage('together-response')
  togetherResponse(socket: Socket, data: any): any {
    // console.log('together-response');
    this.gameService.togetherResponse(socket, data, this.server);
  }
}
