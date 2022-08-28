import { ValidationPipe } from '@nestjs/common';
import { NestFactory } from '@nestjs/core';
import { NestExpressApplication } from '@nestjs/platform-express';
import { join } from 'path';
import { AppModule } from './app.module';
import { DocumentBuilder, SwaggerModule } from '@nestjs/swagger';
import { UsersService } from './users/users.service';

import * as fs from 'fs';
import * as path from 'path';

var cookieParser = require('cookie-parser');

async function bootstrap() {
  const httpsOptions = {
    key: fs.readFileSync(path.join('./private-key.pem')),
    cert: fs.readFileSync(
      path.join('./public-certificate.pem'),
    ),
  };
  const app = await NestFactory.create<NestExpressApplication>(AppModule, {
    httpsOptions,
  });

  const config = new DocumentBuilder()
    .setTitle('Hi-transcendence')
    .setDescription(`transcendence API document description`)
    .setVersion('1.0')
    .build();
  const document = SwaggerModule.createDocument(app, config);
  SwaggerModule.setup('api', app, document);

  app.useStaticAssets(join(__dirname, '../uploads'), {
    prefix: '/public',
  });
  app.use(cookieParser());
  app.enableCors();
  app.useGlobalPipes(new ValidationPipe());

  const userService = app.get(UsersService);
  await userService.initializeStatus();

  await app.listen(3000);
}
bootstrap();
