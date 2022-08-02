import { Injectable } from '@nestjs/common';
import { JwtService } from '@nestjs/jwt';


@Injectable()
export class AuthJwtService {
  constructor(
    private jwtService: JwtService
  ) { }

  async createAcessJwt(intra_id: string) {
    const payload = { intra_id };
    const accessToken = this.jwtService.sign(payload,
      {
        secret: "AcessJwt",
        expiresIn: 60 * 10
      });
    return accessToken;
  }

  async createRefreshJwt(intra_id: string) {
    const payload = { intra_id };
    const refreshToken = this.jwtService.sign(payload,
      {
        secret: "RefreshJwt",
        expiresIn: 60 * 60 * 24 * 7
      });
    return refreshToken;
  }

  jwtVerify(token: string) {
    return this.jwtService.verify(token,
      {
        secret: "AcessJwt"
      });
  }
}
