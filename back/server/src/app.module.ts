import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { StatsModule } from './stats/stats.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Stat } from './stats/entities/stat.entity';
import { UsersModule } from './users/users.module';
import { MatchModule } from './match/match.module';
import { DataSource } from 'typeorm';


@Module({
  imports: [StatsModule,
	UsersModule,
	MatchModule,
	],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
