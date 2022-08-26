import { Controller, Get, Post, Body, Patch, Param, Delete, UseGuards, Res, Query, Req } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { AuthJwtService } from './auth-jwt.service';
import { Response, Request } from 'express';
import { ApiTags, ApiOperation } from '@nestjs/swagger';


@Controller('auth-jwt')
@ApiTags('auth-jwt')
export class AuthJwtController {
  constructor(
    private readonly authJwtService: AuthJwtService) { }

  @Get("access/:intra_id")
  @ApiOperation({ summary: ' ', description: ' ' })
  createaccessJwt(@Param("intra_id") intra_id:string) {
    // console.log("엑세스 토큰 발행");
    return this.authJwtService.createAccessJwt(intra_id);
  }

  @Get("refresh/:intra_id")
  @ApiOperation({ summary: ' ', description: ' ' })
  createRefreshJwt(@Param("intra_id") intra_id:string) {
    // console.log("리프래쉬 토큰 발행");
    return this.authJwtService.createRefreshJwt(intra_id);
  }

  @Get("requestAccessToken")
  @ApiOperation({ summary: ' ', description: ' ' })
  @UseGuards(AuthGuard('jwt-refresh-token'))
  async reCreateAccessJwt(@Req() req:Request) {
    const refreshToken = req.headers.authorization.split('Bearer ')[1]
    const tokens = await this.authJwtService.reCreateAccessJwt(refreshToken);
    return tokens;
  }

  @Get("test")
  @ApiOperation({ summary: ' ', description: ' ' })
  @UseGuards(AuthGuard('jwt-access-token'))
  async test(@Req() req:Request)
  {  
    // console.log(req.headers.authorization.split('Bearer ')[1]);
    // console.log("test확인");
    return "test 확인";
  }
}
