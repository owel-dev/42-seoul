import { Injectable, Module } from '@nestjs/common';
import { MatchService } from './match.service';
import { MatchController } from './match.controller';
import { DatabaseModule } from 'src/database/database.module';
import { matchProviders } from './match.providers';
import { userProviders } from 'src/users/users.providers';
import { statProviders } from 'src/stats/stats.providers';
import { AuthService } from 'src/auth/auth.service';
import { AuthModule } from 'src/auth/auth.module';
import { UsersModule } from 'src/users/users.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Match } from './entities/match.entity';
import { User } from 'src/users/entities/user.entity';
import { AuthJwtModule } from 'src/auth-jwt/auth-jwt.module';


@Module({
  imports: [TypeOrmModule.forFeature([Match, User]), AuthJwtModule],
  controllers: [MatchController],
  providers: [MatchService],
})
export class MatchModule {}
