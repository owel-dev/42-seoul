import { Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Server, Socket } from 'socket.io';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatService } from 'src/chat/chat.service';
import { Stat } from 'src/stats/entities/stat.entity';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { Game } from './game';

@Injectable()
export class GameManager {
    constructor(
        @InjectRepository(User)
        private userRepository: Repository<User>,
        @InjectRepository(Stat)
        private statRepository: Repository<Stat>,
        private chatService: ChatService,
    ) { }

    games = [];
    gameChannelList = [];

    async addNewGame(data: any, server: Server) {
        const game = new Game(data, server);
        this.games.push(game);

        this.chatService.createChannel(
            game.firstPlayer.socket,
            game.channelId,
            server,
        );

        this.chatService.joinChannel(
            game.secondPlayer.socket,
            { channelId: game.channelId },
            server,
        );

        await this.userRepository.update(
            { nickname: data.firstNick },
            { channel_id: game.channelId, status: 'gaming' },
        );

        await this.userRepository.update(
            { nickname: data.secondNick },
            { channel_id: game.channelId, status: 'gaming' },
        );

        game.startGame().then(async (data) => {
            // const stat = this.statRepository.findOne({relations: ['user'], where: {
            // }});
            // stat.win++
            // stat.intra_id =

            await await this.statRepository.save();
            await this.userRepository.update(
                { nickname: game.firstPlayer.nickName },
                { status: 'online' },
            );
            await this.userRepository.update(
                { nickname: game.secondPlayer.nickName },
                { status: 'online' },
            );
        });

        // console.log("games", this.games);

        const getChannelDto = new GetChannelDto();
        getChannelDto.channelId = game.channelId;
        getChannelDto.player1 = game.firstPlayer.nickName;
        getChannelDto.player2 = game.secondPlayer.nickName;
        getChannelDto.curNumUser = 2;
        getChannelDto.maxUser = 10;
        getChannelDto.password = game.password;
        getChannelDto.type = 0;
        getChannelDto.gameMode = game.gameMode;
        // getChannelDto.mode = 'none';

        this.gameChannelList.push(getChannelDto);
    }

    getChannelList() {
        return this.gameChannelList;
    }

    closeGame(channelId: string) {
        // console.log('closegame');

        // this.games.map((game) => {
        //   if (game.channelId === channelId) {
        //     game.stopSendData();
        //   }
        // });
        this.games = this.games.filter((game) => game.gameId !== channelId);
        this.gameChannelList = this.games.filter(
            (gameChannel) => gameChannel.channelId !== channelId,
        );
        // console.log(this.games);
        // console.log(this.gameChannelList);
    }

    changePassword(channelId: string, password: string) {
        for (let game of this.games) {
            if (game.channelId === channelId) {
                game.password = password;
                break;
            }
        }
        for (let gameChannel of this.gameChannelList) {
            if (gameChannel.channelId === channelId) {
                gameChannel.password = password;
                break;
            }
        }
    }

    changeSocket(channelId: string, nickName: string, socket: Socket) {
        for (let game of this.games) {
            if (game.channelId === channelId) {
                if (game.firstPlayer.nickName === nickName) {
                    game.firstPlayer.socket = socket;
                    // console.log('firstPlayer reload');
                    // console.log('firstPlayer reload socket: ', socket.id);
                } else if (game.secondPlayer.nickName === nickName) {
                    // console.log('secondPlayer reload');
                    game.secondPlayer.socket = socket;
                }
                break;
            }
        }
    }

    async isPlayer(user: User): Promise<boolean> {
        const curChannel = this.games.find(
            (game) => game.channelId === user.channel_id,
        );
        if (
            curChannel.firstPlayer === user.nickname ||
            curChannel.secondPlayer === user.nickname
        ) {
            return true;
        } else {
            return false;
        }
    }

    getMode(channelId: string): string {
        // console.log("games: ", this.games);
        for (let game of this.games) {
            if (game.channelId === channelId) {
                // console.log("game.channelId", game.channelId);
                return game.gameMode;
            }
        }
        return undefined;
    }

    getPlayer(channelId: string): any {
        for (let game of this.games) {
            if (game.channelId === channelId) {
                return {
                    firstPlayer: game.firstPlayer.nickName,
                    secondPlayer: game.secondPlayer.nickName
                };
            }
        }
        return undefined;
    }

    stopGame(channelId: string, user: String) {
        for (let game of this.games) {
            if (game.channelId === channelId) {
                game.stopSignal(user);
            }
        }

    }
}
