import { Module } from '@nestjs/common';
import { BanService } from './ban.service';
import { BanController } from './ban.controller';
import { AuthModule } from 'src/auth/auth.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Ban } from './entities/ban.entity';
import { User } from 'src/users/entities/user.entity';

@Module({
  imports: [TypeOrmModule.forFeature([Ban, User]), AuthModule],
  controllers: [BanController],
  providers: [BanService],
  exports: [],
})
export class BanModule {}
