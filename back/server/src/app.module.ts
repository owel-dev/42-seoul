import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { StatsModule } from './stats/stats.module';
import { TypeOrmModule } from '@nestjs/typeorm';
import { Stat } from './stats/entities/stat.entity';
import { UsersModule } from './users/users.module';

@Module({
  imports: [StatsModule,
	TypeOrmModule.forRoot({
		"type": "postgres",
		"host": "localhost",
		"port": 5432,
		"username": "ft",
		"password": "1234",
		"database": "trans",
		"entities": ["dist/**/*.entity{.ts,.js}"],
		"synchronize": true
		}),
	UsersModule,
	],
  controllers: [AppController],
  providers: [AppService],
})
export class AppModule {}
