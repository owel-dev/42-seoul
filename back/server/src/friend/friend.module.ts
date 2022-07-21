import { Module } from '@nestjs/common';
import { FriendService } from './friend.service';
import { FriendController } from './friend.controller';
import { DatabaseModule } from 'src/database/database.module';
import { friendProviders } from './friend.providers';
import { userProviders } from 'src/users/users.providers';
import { AuthService } from 'src/auth/auth.service';

@Module({
	imports: [DatabaseModule],
	controllers: [FriendController],
	providers: [
		...friendProviders,
		...userProviders,
		FriendService,
		AuthService,
	]
})
export class FriendModule {}
