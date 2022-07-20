import { Module } from '@nestjs/common';
import { BanService } from './ban.service';
import { BanController } from './ban.controller';
import { banProviders } from './ban.providers';
import { DatabaseModule } from 'src/database/database.module';
import { userProviders } from 'src/users/users.providers';

@Module({
	imports: [DatabaseModule],
	controllers: [BanController],
	providers: [
		BanService,
		...banProviders,
		...userProviders,
	]
})
export class BanModule {}
