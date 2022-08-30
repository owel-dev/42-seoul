import { Injectable, NotFoundException } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Server, Socket } from 'socket.io';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatService } from 'src/chat/chat.service';
import { Match } from 'src/match/entities/match.entity';
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
    @InjectRepository(Match)
    private matchRepository: Repository<Match>,
  ) {}

  games = [];
  gameChannelList: GetChannelDto[] = [];

  async addNewGame(data: any, server: Server) {
    const game = new Game(data, server);
    this.games.push(game);

    await this.chatService.createChannel(
      game.firstPlayer.socket,
      game.channelId,
      server,
    );

    await this.chatService.joinChannel(
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
      const winPlayer = await this.statRepository.findOne({
        relations: ['user'],
        where: {
          user: { nickname: data.winPlayer },
        },
      });
      winPlayer.win++;
      winPlayer.winrate = 0;
      if (winPlayer.win != 0)
        winPlayer.winrate = winPlayer.win / (winPlayer.win + winPlayer.lose);
      await this.statRepository.save(winPlayer);
      this.userRepository.update(
        { nickname: data.winPlayer },
        { status: 'spectate' },
      );

      const losePlayer = await this.statRepository.findOne({
        relations: ['user'],
        where: {
          user: { nickname: data.losePlayer },
        },
      });
      losePlayer.lose++;
      losePlayer.winrate = 0;
      if (losePlayer.win != 0)
        losePlayer.winrate =
          losePlayer.win / (losePlayer.win + losePlayer.lose);
      await this.statRepository.save(losePlayer);
      this.userRepository.update(
        { nickname: data.losePlayer },
        { status: 'online' },
      );

      const matchData = new Match();
      // console.log('gameMode: ', data);
      matchData.mode = data.gameMode;
      matchData.player_1 = await this.userRepository.findOneBy({
        nickname: data.winPlayer,
      });
      matchData.player_2 = await this.userRepository.findOneBy({
        nickname: data.losePlayer,
      });
      matchData.score_1 = data.winScore;
      matchData.score_2 = data.loseScore;
      this.matchRepository.save(matchData);

      await this.userRepository.update(
        { nickname: game.firstPlayer.nickName },
        { status: 'online' },
      );
      await this.userRepository.update(
        { nickname: game.secondPlayer.nickName },
        { status: 'online' },
      );
    });

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

  getChannelList(): GetChannelDto[] {
    return this.gameChannelList;
  }

  closeGame(channelId: string) {
    // console.log('closegame');

    // this.games.map((game) => {
    //   if (game.channelId === channelId) {
    //     game.stopSendData();
    //   }
    // });
    for (let i = 0; i < this.gameChannelList.length; ++i) {
      if (this.gameChannelList[i].channelId === channelId)
        this.gameChannelList.splice(i, 1);
    }

    // this.gameChannelList = this.games.filter(
    //   (gameChannel) => gameChannel.channelId !== channelId,
    // );
    // console.log(this.games);
    // console.log(this.gameChannelList);
  }

  changePassword(channelId: string, password: string, server: Server) {
    for (const game of this.games) {
      if (game.channelId === channelId) {
        game.password = password;
        break;
      }
    }
    for (const gameChannel of this.gameChannelList) {
      if (gameChannel.channelId === channelId) {
        gameChannel.password = password;
        break;
      }
    }
    server.emit('gamelist-update');
  }

  changeSocket(channelId: string, nickName: string, socket: Socket) {
    for (const game of this.games) {
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

  isPlayer(user: User): boolean{
    const curChannel = this.games.find(
      (game) => game.channelId === user.channel_id,
    );
    // console.log("in-isPlayer", curChannel.firstPlayer, curChannel.secondPlayer, user.nickname);
    if (
      curChannel.firstPlayer.nickName === user.nickname ||
      curChannel.secondPlayer.nickName === user.nickname
    ) {
      return true;
    } else {
      return false;
    }
  }

  getMode(channelId: string): string {
    // console.log("games: ", this.games);
    for (const game of this.games) {
      if (game.channelId === channelId) {
        // console.log("game.channelId", game.channelId);
        return game.gameMode;
      }
    }
    return undefined;
  }

  getPlayer(channelId: string): any {
    for (const game of this.games) {
      if (game.channelId === channelId) {
        return {
          firstPlayer: game.firstPlayer.nickName,
          secondPlayer: game.secondPlayer.nickName,
        };
      }
    }
    return {
      firstPlayer: undefined,
      secondPlayer: undefined,
    };
  }

  getPassword(channelId: string): any {
    for (const game of this.games) {
      if (game.channelId === channelId) {
        return {
          password: game.password,
        };
      }
    }
    return { password: undefined };
  }

  stopGame(channelId: string, user: string) {
    // console.log('@stopgame');
    for (const game of this.games) {
      if (game.channelId === channelId) {
        game.onStopSignal(user);
      }
    }
  }
}
