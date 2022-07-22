import { Module } from '@nestjs/common';
import { FriendService } from './friend.service';
import { FriendController } from './friend.controller';
import { DatabaseModule } from 'src/database/database.module';
import { friendProviders } from './friend.providers';
import { userProviders } from 'src/users/users.providers';
import { AuthService } from 'src/auth/auth.service';
import { AuthModule } from 'src/auth/auth.module';

@Module({
	imports: [DatabaseModule, AuthModule],
	controllers: [FriendController],
	providers: [
		...friendProviders,
		...userProviders,
		FriendService,
	]
})
export class FriendModule { }
