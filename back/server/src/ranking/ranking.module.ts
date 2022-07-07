import { Module } from '@nestjs/common';
import { RankingService } from './ranking.service';
import { RankingController } from './ranking.controller';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Stat } from 'src/stats/entities/stat.entity';

@Module({
  imports: [TypeOrmModule.forFeature([Stat])],
  controllers: [RankingController],
  providers: [RankingService]
})
export class RankingModule {}
