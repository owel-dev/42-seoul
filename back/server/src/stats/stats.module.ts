import { Module } from '@nestjs/common';
import { StatsService } from './stats.service';
import { StatsController } from './stats.controller';
import { DatabaseModule } from 'src/database/database.module';
import { statProviders } from './stats.providers';
import { userProviders } from 'src/users/users.providers';
import { AuthService } from 'src/auth/auth.service';

@Module({
  imports: [DatabaseModule],
  controllers: [StatsController],
  providers: [
	  ...statProviders,
	  ...userProviders,
	  StatsService,
	  AuthService]
})
export class StatsModule {}
