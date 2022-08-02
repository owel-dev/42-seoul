import { Global, Module } from '@nestjs/common';
import { StatsService } from './stats.service';
import { StatsController } from './stats.controller';
import { DatabaseModule } from 'src/database/database.module';
import { statProviders } from './stats.providers';
import { userProviders } from 'src/users/users.providers';
import { AuthService } from 'src/auth/auth.service';
import { AuthModule } from 'src/auth/auth.module';
import { UsersModule } from 'src/users/users.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Stat } from './entities/stat.entity';
import { User } from 'src/users/entities/user.entity';
import { AuthJwtModule } from 'src/auth-jwt/auth-jwt.module';

@Global()
@Module({
  imports: [TypeOrmModule.forFeature([Stat, User]), AuthJwtModule],
  controllers: [StatsController],
  providers: [StatsService],
})
export class StatsModule {}
