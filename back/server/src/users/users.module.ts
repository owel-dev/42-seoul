import { Module } from '@nestjs/common';
import { UsersService } from './users.service';
import { UsersController } from './users.controller';

import { AuthModule } from 'src/auth/auth.module';

import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from './entities/user.entity';
import { Friend } from 'src/friend/entities/friend.entity';
import { Ban } from 'src/ban/entities/ban.entity';
import { Match } from 'src/match/entities/match.entity';
import { AuthJwtModule } from 'src/auth-jwt/auth-jwt.module';

@Module({
  imports: [TypeOrmModule.forFeature([User, Friend, Ban, Match]),AuthModule, AuthJwtModule],
  controllers: [UsersController],
  providers: [UsersService],
  exports: [UsersService],
})
export class UsersModule {}
