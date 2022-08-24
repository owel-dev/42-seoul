import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AuthModule } from 'src/auth/auth.module';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatModule } from 'src/chat/chat.module';
import { Match } from 'src/match/entities/match.entity';
import { Stat } from 'src/stats/entities/stat.entity';
import { User } from 'src/users/entities/user.entity';
import { GameManager } from './game-manager';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';
import { MatchManager } from './match-manager';

@Module({
  imports: [
    AuthModule,
    TypeOrmModule.forFeature([User, Stat, Match]),
    ChatModule,
  ],
  controllers: [],
  providers: [
    GameGateway,
    GameService,
    GetChannelDto,
    MatchManager,
    GameManager,
  ],
  exports: [GameManager, GameService, MatchManager],
})
export class GameModule {}
