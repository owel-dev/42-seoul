import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { StatsModule } from './stats/stats.module';
import { UsersModule } from './users/users.module';
import { MatchModule } from './match/match.module';
import { ChannelModule } from './channel/channel.module';
import { FriendModule } from './friend/friend.module';
import { BanModule } from './ban/ban.module';
import { GameModule } from './game/game.module';
import { AuthModule } from './auth/auth.module';
import { ConfigModule, ConfigService } from '@nestjs/config';
import { MailerModule } from '@nestjs-modules/mailer';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Friend } from './friend/entities/friend.entity';
import { Ban } from './ban/entities/ban.entity';
import { Stat } from './stats/entities/stat.entity';
import { Match } from './match/entities/match.entity';
import { User } from './users/entities/user.entity';
import { AuthJwtModule } from './auth-jwt/auth-jwt.module';
import { ChatModule } from './chat/chat.module';
import { ConnectModule } from './connect/connect.module';

@Module({
  imports: [
    StatsModule,
    UsersModule,
    MatchModule,
    ChannelModule,
    FriendModule,
    BanModule,
    GameModule,
    AuthModule,
    AuthJwtModule,
    ConnectModule,
    ConfigModule.forRoot({
      isGlobal: true,
    }),
    MailerModule.forRootAsync({
      useFactory: async (config: ConfigService) => ({
        transport: {
          host: config.get('MAIL_HOST'),
          secure: false,
          auth: {
            user: config.get('MAIL_USER'),
            pass: config.get('MAIL_PASSWORD'),
          },
        },
      }),
      inject: [ConfigService],
    }),
    ChatModule,
    TypeOrmModule.forRootAsync({
      imports: [ConfigModule],
      useFactory: (config: ConfigService) => ({
        type: 'postgres',
        host: config.get('DB_HOST'),
        port: config.get('DB_PORT'),
        username: config.get('DB_USERNAME'),
        password: config.get('DB_PASSWORD'),
        database: config.get('DB_DATABASE'),
        entities: [User, Friend, Ban, Stat, Match],
        synchronize: false,
      }),
      inject: [ConfigService],
    }),
  ],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
