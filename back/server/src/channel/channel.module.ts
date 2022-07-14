import { Module } from '@nestjs/common';
import { ChannelService } from './channel.service';
import { ChannelController } from './channel.controller';
import { channelProviders } from './channel.providers';
import { DatabaseModule } from 'src/database/database.module';

@Module({
  imports: [DatabaseModule],
  controllers: [ChannelController],
  providers: [
    ...channelProviders,
    ChannelService
  ]
})
export class ChannelModule {}
