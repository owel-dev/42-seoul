import { Module } from '@nestjs/common';
import { AuthService } from './auth.service';
import { AuthController } from './auth.controller';
import { userProviders } from 'src/users/users.providers';
import { DatabaseModule } from 'src/database/database.module';

@Module({
	imports: [DatabaseModule],
	controllers: [AuthController],
	providers: [
		...userProviders,
		AuthService,
	],
	exports: [AuthService],
})
export class AuthModule { }
