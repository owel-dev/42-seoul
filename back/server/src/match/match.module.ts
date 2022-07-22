import { Injectable, Module } from '@nestjs/common';
import { MatchService } from './match.service';
import { MatchController } from './match.controller';
import { DatabaseModule } from 'src/database/database.module';
import { matchProviders } from './match.providers';
import { userProviders } from 'src/users/users.providers';
import { statProviders } from 'src/stats/stats.providers';
import { AuthService } from 'src/auth/auth.service';
import { AuthModule } from 'src/auth/auth.module';

@Module({
	imports: [DatabaseModule, AuthModule],
	controllers: [MatchController],
	providers: [
		...userProviders,
		...matchProviders,
		MatchService,
	],
})
export class MatchModule { }
