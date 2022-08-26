import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { ConfigService } from '@nestjs/config';
import { PassportStrategy } from '@nestjs/passport';
import { InjectRepository } from '@nestjs/typeorm';
import { ExtractJwt, Strategy } from 'passport-jwt';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';

@Injectable()
export class JwtRefreshStrategy extends PassportStrategy(
  Strategy,
  'jwt-refresh-token',
) {
  constructor(
    private config: ConfigService,
    @InjectRepository(User)
    private userRepository: Repository<User>,
  ) {
    super({
      secretOrKey: config.get('JWT_REFRESH_SECRET'),
      jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
      ignoreExpiration: true,
    });
  }

  async validate(payload: any) {
    const now = new Date().getTime() / 1000;
    const exp = payload.exp;
    // console.log('JwtRefreshStrategy ', exp - now);
    if (exp - now < 0) {
      this.userRepository.update(
        { intra_id: payload.intra_id },
        { is_second_auth: false },
      );
      throw new HttpException(
        { statusCode: 400, error: '만료된 리프래쉬 토큰입니다.' },
        HttpStatus.UNAUTHORIZED,
      );
    }
    return 'JwtRefreshStrategy 확인';
  }
}
