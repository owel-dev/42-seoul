import { Module } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';
import { DatabaseModule } from 'src/database/database.module';
import { userProviders } from './users.providers';
import { friendProviders } from 'src/friend/friend.providers';
import { banProviders } from 'src/ban/ban.providers';
import { AuthModule } from 'src/auth/auth.module';
import { AuthService } from 'src/auth/auth.service';

@Module({
	imports: [DatabaseModule, AuthModule],
	controllers: [UsersController],
	providers: [
		...userProviders,
		...friendProviders,
		...banProviders,
		UsersService,
	],
})
export class UsersModule { }
