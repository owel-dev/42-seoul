import { Module } from '@nestjs/common';
import { AuthJwtService } from './auth-jwt.service';
import { AuthJwtController } from './auth-jwt.controller';
import { JwtModule } from '@nestjs/jwt';
import { PassportModule } from '@nestjs/passport';
import { JwtAcessStrategy } from './auth-jwt.stategyAcess';
import { TypeOrmModule } from '@nestjs/typeorm';
import { User } from "src/users/entities/user.entity";
import { JwtRefreshStrategy } from './auth-jwt.stategyRefresh';

@Module({
  imports: [
    TypeOrmModule.forFeature([User]),
    PassportModule.register({defaultStrategy:'jwt'}),
    JwtModule.register({
      secret: "Secret1234",
      signOptions:{
        expiresIn: 60 * 60 * 10
      }
    })
  ],
  controllers: [AuthJwtController],
  providers: [
     AuthJwtService, JwtAcessStrategy, JwtRefreshStrategy
  ],
  exports: [AuthJwtService, JwtAcessStrategy, JwtRefreshStrategy, PassportModule]
})

export class AuthJwtModule {}
