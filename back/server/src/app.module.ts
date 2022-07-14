import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { StatsModule } from './stats/stats.module';
import { UsersModule } from './users/users.module';
import { MatchModule } from './match/match.module';
import { ChannelModule } from './channel/channel.module';
import { FriendModule } from './friend/friend.module';

@Module({
	imports: [
		StatsModule,
		UsersModule,
		MatchModule,
		ChannelModule,
		FriendModule
	],
	controllers: [AppController],
	providers: [AppService],
})
export class AppModule {}
