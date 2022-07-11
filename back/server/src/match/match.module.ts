import { Injectable, Module } from '@nestjs/common';
import { MatchService } from './match.service';
import { MatchController } from './match.controller';
import { Match } from './entities/match.entity';
import { TypeOrmModule } from '@nestjs/typeorm';
import { DataSource } from 'typeorm';
import { DatabaseModule } from 'src/database/database.module';
import { matchProviders } from './match.providers';

@Module({
  imports: [DatabaseModule],
  controllers: [MatchController],
  providers: [
	...matchProviders,
	MatchService,
],
})
@Injectable()
export class MatchModule {}
