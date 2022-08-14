import { Module } from '@nestjs/common';
import { TypeOrmModule } from '@nestjs/typeorm';
import { AuthModule } from 'src/auth/auth.module';
import { ChatModule } from 'src/chat/chat.module';
import { GameModule } from 'src/game/game.module';
import { User } from 'src/users/entities/user.entity';
import { ConnectGateway } from './connect.gateway';
import { ConnectService } from './connect.service';

@Module({
  imports: [TypeOrmModule.forFeature([User]), GameModule, AuthModule, ChatModule],
  providers: [ConnectGateway, ConnectService]
})
export class ConnectModule { }
