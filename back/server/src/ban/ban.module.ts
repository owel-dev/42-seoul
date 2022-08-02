import { Module } from '@nestjs/common';
import { BanService } from './ban.service';
import { BanController } from './ban.controller';
import { AuthModule } from 'src/auth/auth.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Ban } from './entities/ban.entity';
import { User } from 'src/users/entities/user.entity';
import { AuthJwtModule } from 'src/auth-jwt/auth-jwt.module';

@Module({
  imports: [TypeOrmModule.forFeature([Ban, User]), AuthJwtModule],
  controllers: [BanController],
  providers: [BanService],
  exports: [],
})
export class BanModule {}
