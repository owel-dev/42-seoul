import { ForbiddenException, HttpException, Injectable, UnauthorizedException } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { JwtService } from '@nestjs/jwt';


@Injectable()
export class AuthJwtService {
  constructor(
    private jwtService: JwtService,
    private config: ConfigService
  ) { }

  async createAccessJwt(intra_id: string) {
    const payload = { intra_id };
    const accessToken = this.jwtService.sign(payload,
      {
        secret: this.config.get("JWT_ACCESS_SECRET"),
        expiresIn: 60 * 30
      });
    return accessToken;
  }

  async createRefreshJwt(intra_id: string) {
    const payload = { intra_id };
    const refreshToken = this.jwtService.sign(payload,
      {
        secret: this.config.get("JWT_REFRESH_SECRET"),
        expiresIn: 60 * 60 * 24 * 14
      });
    return refreshToken;
  }

  async reCreateAccessJwt(token: string) {
    const payload = this.jwtService.verify(token,
      { secret: this.config.get("JWT_REFRESH_SECRET") }
    );
    let refreshToken = null;
    const now = new Date().getTime() / 1000;
    const exp = payload.exp;
    const accessToken = await this.createAccessJwt(payload.intra_id);
    if (exp - now < 60 * 60 * 3) {
      refreshToken = await this.createRefreshJwt(payload.intra_id);
    }
    const tokens = { accessToken: accessToken, refreshToken: refreshToken };
    return tokens;
  }

  async jwtVerify(token: string) {
    let info;
    try {
      info = await this.jwtService.verify(token,
        {
          secret: this.config.get("JWT_ACCESS_SECRET"),
        });
    }
    catch (err) {
      // console.log("jwtVerify 에러 발생");
      // 토큰이 만료되거나 토큰정보가 일치하지 않았을떄.
      // throw new HttpException(
      //   { statusCode: 'SC01', error: '잘못된 코드입니다.' },
      //   HttpStatus.BAD_REQUEST,
      // );      
      // throw new UnauthorizedException();
      // return undefined;
    }
    return info;
  }
}
