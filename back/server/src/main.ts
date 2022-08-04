import { ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { NestExpressApplication } from '@nestjs/platform-express';
import { join } from 'path';
import { ArgumentOutOfRangeError } from 'rxjs';
import { AppModule } from './app.module';
var cookieParser = require('cookie-parser')

async function bootstrap() {
	const app = await NestFactory.create<NestExpressApplication>(AppModule);
	app.useStaticAssets(join(__dirname, '../dist/uploads'), {
		prefix: '/public',
	  });
	app.use(cookieParser());
	app.enableCors();
	app.useGlobalPipes(new ValidationPipe());
	await app.listen(3000);
}
bootstrap();
