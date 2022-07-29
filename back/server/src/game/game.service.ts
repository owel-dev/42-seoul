import { Injectable } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatService } from 'src/chat/chat.service';
import { Game, User } from './game';

const users = {};
let matchmaking = [];
const games = {};
const gameList: GetChannelDto[] = [];

@Injectable()
export class GameService {
  constructor(private chatService: ChatService) {}

  setGameData(server: Server) {
    setInterval(() => {
      for (const key in games) {
        const game = games[key];

        game.update();

        if (
          game.players[game.player1].score == 10 ||
          game.players[game.player2].score == 10
        ) {
          delete games[key];
          users[game.player1].socket.emit('game-end', game.id);
          users[game.player2].socket.emit('game-end', game.id);
          server.to(game.id).emit('game-end', game.id);
          for (let i = 0; i < gameList.length; ++i) {
            if (gameList[i].channelId == game.id) gameList.splice(i, 1);
          }
          continue;
        }

        const data = {
          firstPlayerScore: game.players[game.player1].score,
          secondPlayerScore: game.players[game.player2].score,
          firstPlayerPaddle: game.players[game.player1].pos,
          secondPlayerPaddle: game.players[game.player2].pos,
          ball: game.ball,
        };
        users[game.player2].socket.emit('game-data', data, (callback) => {
          game.players[game.player2].pos = callback;
        });
        users[game.player1].socket.emit('game-data', data, (callback) => {
          game.players[game.player1].pos = callback;
        });
        server.to(game.id).emit('game-data', data);
      }
    }, (1 / 40) * 1000);
  }

  handleConnection(socket: Socket) {
    console.log(`New client connected: ${socket.id}`);
  }

  handleDisconnect(socket: Socket) {
    console.log(`Client Disconnected: ${socket.id}`);
    delete users[socket.id];
    if (matchmaking.length != 0 && matchmaking[0] == socket.id) {
      matchmaking = [];
    }
    for (const key in games) {
      const game = games[key];
      if (game.player1 == socket.id) {
        delete games[key];
      } else if (game.player2 == socket.id) {
        delete games[key];
      }
    }
  }

  sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
  }

  async matchMaker(new_player: string, data: any, server: Server) {
    if (matchmaking.length != 0) {
      //* 게임 대기 화면
      const game = new Game(
        matchmaking[0],
        users[matchmaking[0]].username,
        new_player,
        users[new_player].username,
        data.password,
        data.mode,
      );

      users[matchmaking[0]].socket.emit('game-wait', {
        channelId: game.id,
        firstPlayer: users[matchmaking[0]].username,
        secondPlayer: users[new_player].username,
      });
      users[new_player].socket.emit('game-wait', {
        channelId: game.id,
        firstPlayer: users[matchmaking[0]].username,
        secondPlayer: users[new_player].username,
      });

      for (let i = 5; i >= 0; --i) {
        if (i != 0) {
          users[matchmaking[0]].socket.emit('count-down', i.toString());
          users[new_player].socket.emit('count-down', i.toString());
        } else {
          users[matchmaking[0]].socket.emit('count-down', 'Game Start!');
          users[new_player].socket.emit('count-down', 'Game Start!');
        }
        await this.sleep(1000);
      }

      games[game.id] = game;

      const dto = new GetChannelDto();
      dto.channelId = game.id;
      dto.curNumUser = 2;
      dto.maxUser = 10;
      dto.mode = game.mode;
      dto.password = game.password;
      dto.player1 = game.players[game.player1].name;
      dto.player2 = game.players[game.player2].name;
      dto.type = 0;

      gameList.push(dto);

      await this.chatService.createChannel(
        users[matchmaking[0]].socket,
        game.id,
        server,
      );

      await this.chatService.joinChannel(
        users[new_player].socket,
        { channelId: game.id },
        server,
      );

      matchmaking = [];
    } else {
      matchmaking.push(new_player);
    }
  }

  matchRequest(socket: Socket, data: any, server: Server): void {
    users[socket.id] = new User(socket);
    users[socket.id].username = data.username;

    this.matchMaker(socket.id, data, server);
  }

  spectateRequest(socket: Socket, data: any, server: Server): void {
    console.log('spec gameId: ', data.gameId);
    socket.join(data.gameId);
    this.chatService.joinChannel(socket, data.gameId, server);
  }

  gamelistRequest(): any {
    return { channelList: gameList };
  }

  changePassword(data: any): void {
    console.log('id: %s, password: %d', data.channelId, data.password);
    games[data.channelId].password = data.password;
    for (const x of gameList) {
      if (x.channelId === data.channelId) x.password = data.password;
    }
  }

  submitPassword(data: any): boolean {
    if (!data.password || !data.channelId) return false;
    console.log('password: ', data.password);
    console.log('channel: ', data.channelId);
    return games[data.channelId].password === data.password;
  }
}
