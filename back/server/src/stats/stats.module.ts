import { Module } from '@nestjs/common';
import { StatsService } from './stats.service';
import { StatsController } from './stats.controller';
import { DatabaseModule } from 'src/database/database.module';
import { statProviders } from './stats.providers';

@Module({
  imports: [DatabaseModule],
  controllers: [StatsController],
  providers: [
	  ...statProviders,
	  StatsService]
})
export class StatsModule {}
