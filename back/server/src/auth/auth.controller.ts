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
import { ConfigService } from '@nestjs/config';
import { Response, Request } from 'express';
import { ResUserNavi } from 'src/users/dto/res-user-navi.dto';
import { AuthService } from './auth.service';

@Controller('oauth')
export class AuthController {
  constructor(
    private readonly authService: AuthService,
    private config: ConfigService,
  ) {}

  @Get('test')
  test(@Req() req: Request) {
    console.log(req.cookies);
  }

  @Get('login')
  async saveAccessToken(@Res() res: Response, @Query('code') code: string) {
    await this.authService.saveAccessToken(res, code);
  }

  @Patch('logout')
  async logout() {
    //클라이언트 측에서 토큰 삭제하고 소켓 연결 끊어주기만 하면 될듯.
    return;
  }

  @Redirect(
    'https://api.intra.42.fr/oauth/authorize?client_id=10fd003cd72e573d39cefc1302e9a5c3a9722ad06f7bffe91bf3b3587ace5036&redirect_uri=http%3A%2F%2F10.19.236.57%3A3000%2Foauth%2Flogin&response_type=code',
    302,
  )
  @Get('42')
  getOauthPage() {
    // console.log('authorization/42');
    return;
  }

  @Post('sendEmail')
  async sendEmail(
    @Query('id') id: string,
    @Body('email') email: string,
  ): Promise<void> {
    await this.authService.sendEmail(id, email);
  }

  @Post('validEmail')
  async validEmail(
    @Query('id') id: string,
    @Body('code') code: string,
  ): Promise<ResUserNavi> {
    return await this.authService.validEmail(id, code);
  }
}
