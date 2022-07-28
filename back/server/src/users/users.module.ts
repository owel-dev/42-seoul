import { forwardRef, Module } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';
import { DatabaseModule } from 'src/database/database.module';
import { userProviders } from './users.providers';
import { friendProviders } from 'src/friend/friend.providers';
import { banProviders } from 'src/ban/ban.providers';
import { AuthModule } from 'src/auth/auth.module';
import { AuthService } from 'src/auth/auth.service';
import { FriendModule } from 'src/friend/friend.module';
import { BanModule } from 'src/ban/ban.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './entities/user.entity';
import { Friend } from 'src/friend/entities/friend.entity';
import { Ban } from 'src/ban/entities/ban.entity';
import { Match } from 'src/match/entities/match.entity';
import { ChatModule } from 'src/chat/chat.module';

@Module({
  imports: [
    TypeOrmModule.forFeature([User, Friend, Ban, Match]),
    AuthModule,
    forwardRef(() => ChatModule),
  ],
  controllers: [UsersController],
  providers: [UsersService],
  exports: [UsersService],
})
export class UsersModule {}
