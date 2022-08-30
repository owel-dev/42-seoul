import {
  Body,
  Controller,
  Get,
  Param,
  Patch,
  Post,
  Query,
  Redirect,
  Req,
  Res,
} from '@nestjs/common';
import { Response } from 'express';
import { ResUserNavi } from 'src/users/dto/res-user-navi.dto';
import { AuthService } from './auth.service';
import { ApiTags, ApiOperation } from '@nestjs/swagger';
import { ConfigService } from '@nestjs/config';

@Controller('oauth')
@ApiTags('auth(인증) API')
export class AuthController {
  constructor(private readonly authService: AuthService, 
    private config: ConfigService) { }

  @Get('test')
  @ApiOperation({ summary: '테스트 API', description: '테스트 API' })
  async testLogin(@Res() response: Response) {
    // console.log("testLogin");
    await this.authService.testLogin(response);
  }

  @Get('login')
  @ApiOperation({
    summary: '사이트 로그인 API',
    description: '사이트에 로그인을 시도합니다. /oauth/42로부터 Redirect.',
  })
  async saveAccessToken(@Res() res: Response, @Query('code') code: string) {
    await this.authService.saveAccessToken(res, code);
  }

  @Patch('logout')
  @ApiOperation({
    summary: '로그아웃 API',
    description: '로그아웃을 시도한다.',
  })
  async logout() {
    //클라이언트 측에서 토큰 삭제하고 소켓 연결 끊어주기만 하면 될듯.
    return;
  }

  @ApiOperation({
    summary: '42 Oauth API 로그인',
    description: '42 Oauth API에 로그인을 시도한다.',
  })
  @Get('42')
  getOauthPage(@Res() res: Response) {
    // console.log('authorization/42');
    res.redirect(this.config.get('REDIRECT_INTRA'))
    res.status(302)
    return ;
  }

  @Post('sendEmail')
  @ApiOperation({
    summary: '2차 인증 이메일 전송 API',
    description: '2차 인증을 위해 이메일을 전송한다.',
  })
  async sendEmail(
    @Query('id') id: string
  ): Promise<void> {
    await this.authService.sendEmail(id);
  }

  @Post('validEmail')
  @ApiOperation({
    summary: '2차 인증 이메일 확인 API',
    description: '2차 인증을 위해 이메일로 전송된 코드를 확인한다.',
  })
  async validEmail(
    @Query('id') id: string,
    @Body('code') code: string,
  ): Promise<ResUserNavi> {
    return await this.authService.validEmail(id, code);
  }
}
