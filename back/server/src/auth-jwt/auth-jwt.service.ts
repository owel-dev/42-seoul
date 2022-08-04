import { Injectable } from '@nestjs/common';
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
        secret: this.config.get("JWT_SECRET_ACCESS"),
        expiresIn: 60 * 60
      });
    return accessToken;
  }

  async createRefreshJwt(intra_id: string) {
    const payload = { intra_id };
    const refreshToken = this.jwtService.sign(payload,
      {
        secret: this.config.get("JWT_SECRET_REFRESH"),
        expiresIn: 60 * 60 * 24 * 7
      });
    return refreshToken;
  }

  async jwtVerify(token: string) {
    return await this.jwtService.verify(token,
      {
        secret: this.config.get("JWT_SECRET_ACCESS"),
      });
  }
}
