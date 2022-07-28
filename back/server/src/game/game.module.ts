import { Module } from '@nestjs/common';
import { GetChannelDto } from 'src/channel/dto/get-channelList.dto';
import { ChatModule } from 'src/chat/chat.module';
import { GameGateway } from './game.gateway';
import { GameService } from './game.service';

@Module({
  imports: [ChatModule],
  controllers: [],
  providers: [GameGateway, GameService, GetChannelDto],
})
export class GameModule {}
