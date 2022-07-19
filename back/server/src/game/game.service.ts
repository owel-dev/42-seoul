import { Injectable } from '@nestjs/common';
import { Server, Socket } from 'socket.io';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { Game, User } from './game';
import { GameGateway } from './game.gateway';

var uNRegex = new RegExp('^[a-zA-Z0-9_.-]{3,}$');
var users = {};
var matchmaking = [];
var games = {};
var gameList: GetChannelDto[] = [];

@Injectable()
export class GameService {
    constructor(
        private readonly gameService: GetChannelDto,
    ) { }

    setGameData(server: Server) {
        const interv = setInterval(() => {
            for (let key in games) {
                let game = games[key];

                game.update();

                if (game.players[game.player1].score == 3 || game.players[game.player2].score == 3) {
                    delete games[key];
                    console.log("games: ", games[key]);
                    users[game.player1].socket.emit('game-end', game.id);
                    users[game.player2].socket.emit('game-end', game.id);
                    server.to(game.id).emit('game-end', game.id);
                    for (let i = 0; i < gameList.length; ++i) {
                        if (gameList[i].channelId == game.id)
                            gameList.splice(i, 1);
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
                users[game.player2].socket.emit(
                    'game-data',
                    data,
                    (callback) => {
                        game.players[game.player2].pos = callback;
                    },
                );
                users[game.player1].socket.emit(
                    'game-data',
                    data,
                    (callback) => {
                        game.players[game.player1].pos = callback;
                    },
                );
                server.to(game.id).emit('game-data', data);
            }
        }, (1 / 40) * 1000);
        // }, 1000);
    }

    handleConnection(socket: Socket) {
        console.log(`New client connected: ${socket.id}`);
    }

    handleDisconnect(socket: Socket) {
        // console.log(`Client Disconnected: ${users[socket.id].username}`);
        delete users[socket.id];
        socket.broadcast.emit('player-broadcast', Object.keys(users).length);
        if (matchmaking.length != 0 && matchmaking[0] == socket.id) {
            matchmaking = [];
        }

        for (let key in games) {
            let game = games[key];
            if (game.player1 == socket.id) {
                users[game.player2].socket.emit('player-left');
                delete games[key];
            } else if (game.player2 == socket.id) {
                users[game.player1].socket.emit('player-left');
                delete games[key];
            }
        }
    }

    sleep(ms) {
        return new Promise((resolve) => setTimeout(resolve, ms));
    }

    async matchMaker(server: Server, new_player) {
        if (matchmaking.length != 0) {
            //* 게임 대기 화면
            var game = new Game(
                matchmaking[0],
                users[matchmaking[0]].username,
                new_player,
                users[new_player].username,
            );

            users[matchmaking[0]].socket.emit('game-wait', { channelId: game.id });
            users[new_player].socket.emit('game-wait', { channelId: game.id });

            for (let i = 5; i >= 0; --i) {
                if (i != 0) {
                    users[matchmaking[0]].socket.emit('count-down', i.toString());
                    users[new_player].socket.emit('count-down', i.toString());
                }
                else {
                    users[matchmaking[0]].socket.emit('count-down', 'Game Start!');
                    users[new_player].socket.emit('count-down', 'Game Start!');
                }
                // console.log("count: ", i);
                await this.sleep(1000);
            }
            games[game.id] = game;

            // users[matchmaking[0]].socket.join(game.id);
            // users[new_player].socket.join(game.id);

            const dto = new GetChannelDto();
            dto.channelId = game.id;
            dto.curNumUser = 2;
            dto.maxUser = 10;
            dto.mode = 0;
            dto.password = game.password;
            dto.player1 = game.players[game.player1].name;
            dto.player2 = game.players[game.player2].name;
            dto.type = 0;

            gameList.push(dto);
            server.emit('game-created', { gameId: game.id, password: game.password });
            matchmaking = [];
        } else {
            matchmaking.push(new_player);
        }
    }

    matchRequest(server: Server, socket: Socket, data: any): void {
        users[socket.id] = new User(socket);
        users[socket.id].username = data.username;
        this.matchMaker(server, socket.id);
    }

    spectateRequest(server: Server, socket: Socket, data: any): void {
        // socket.emit('spectate-response');
        socket.join(data.gameId);
    }

    gamelistRequest(server: Server, socket: Socket): any {
        return { channelList: gameList };
    }







}
