import { forwardRef, Module } from '@nestjs/common';
import { FriendService } from './friend.service';
import { FriendController } from './friend.controller';
import { DatabaseModule } from 'src/database/database.module';
import { friendProviders } from './friend.providers';
import { userProviders } from 'src/users/users.providers';
import { AuthService } from 'src/auth/auth.service';
import { AuthModule } from 'src/auth/auth.module';
import { UsersModule } from 'src/users/users.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Friend } from './entities/friend.entity';
import { User } from 'src/users/entities/user.entity';
import { AuthJwtModule } from 'src/auth-jwt/auth-jwt.module';

@Module({
  imports: [TypeOrmModule.forFeature([Friend, User]),AuthModule ,AuthJwtModule],
  controllers: [FriendController],
  providers: [FriendService],
  exports: [FriendService],
})
export class FriendModule {}
