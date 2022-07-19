import { Module } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';
import { DatabaseModule } from 'src/database/database.module';
import { userProviders } from './users.providers';
import { friendProviders } from 'src/friend/friend.providers';
import { banProviders } from 'src/ban/ban.providers';

@Module({
  imports: [DatabaseModule],
  controllers: [UsersController],
  providers: [
	...userProviders,
	...friendProviders,
	...banProviders,
	UsersService,
	],
})
export class UsersModule {}
