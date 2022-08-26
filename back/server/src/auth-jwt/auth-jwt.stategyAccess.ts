import { HttpException, HttpStatus, Injectable, UnauthorizedException } from "@nestjs/common";
import { PassportStrategy } from "@nestjs/passport";
import { ExtractJwt, Strategy } from "passport-jwt"
import { ConfigService } from "@nestjs/config";

@Injectable()
export class JwtAccessStrategy extends PassportStrategy(Strategy, 'jwt-access-token') {
    constructor(
        private config: ConfigService

    ) {
        super({
            secretOrKey: config.get("JWT_ACCESS_SECRET"),
            jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
            ignoreExpiration: true
        })
    }
    async validate(payload: any) {
        const now = new Date().getTime() / 1000;
        const exp = payload.exp;

        // console.log("JwtAccessStrategy ", exp - now);

        if (exp - now < 0)
        {
            throw new HttpException(
                { statusCode: 401, 
                error: '만료된 엑세스 토큰입니다.' 
            },
                HttpStatus.UNAUTHORIZED,
            )
        }
        return "JwtaccessStrategy 확인";
    }
}
