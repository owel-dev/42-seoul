import { Module } from '@nestjs/common';
import { StatsService } from './stats.service';
import { StatsController } from './stats.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Stat } from './entities/stat.entity';
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
