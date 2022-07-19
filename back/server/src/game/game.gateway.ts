import { Injectable } from '@nestjs/common';
import {
  MessageBody,
  OnGatewayConnection,
  OnGatewayDisconnect,
  OnGatewayInit,
  SubscribeMessage,
  WebSocketGateway,
  WebSocketServer,
  WsResponse,
} from '@nestjs/websockets';
import { resolve } from 'path/posix';
import { emit } from 'process';
import { Server, Socket } from 'socket.io';
import { Game, User } from './game';
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

  afterInit(server: any) {
    this.gameService.setGameData(this.server);
  }


  handleConnection(socket: Socket) {
    this.gameService.handleConnection(socket);
    // console.log("",this.server);
  }

  handleDisconnect(socket: Socket) {
    this.gameService.handleDisconnect(socket);
  }

  @SubscribeMessage('match-request')
  matchRequest(socket: Socket, data: any): void {
    this.gameService.matchRequest(this.server, socket, data);
  }

  // socket.on('get-ping', (callback) => {
  //     callback(true);
  //   });
}
