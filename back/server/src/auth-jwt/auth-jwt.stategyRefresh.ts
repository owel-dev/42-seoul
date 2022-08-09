import { HttpException, HttpStatus, Injectable } from "@nestjs/common";
import { ConfigService } from "@nestjs/config";
import { PassportStrategy } from "@nestjs/passport";
import { ExtractJwt, Strategy } from "passport-jwt";

@Injectable()
export class JwtRefreshStrategy extends PassportStrategy(Strategy, 'jwt-refresh-token') {
    constructor(
        private config: ConfigService
    ) {
        super({
            secretOrKey: config.get("JWT_REFRESH_SECRET"),
            jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
            ignoreExpiration: true
        })
    }

    async validate(payload: any)
    {
        const now = new Date().getTime() / 1000;
        const exp = payload.exp;
        console.log("JwtRefreshStrategy ", exp - now);

        if (exp - now < 0)
        {
            throw new HttpException(
                { statusCode: 400, 
                error: '만료된 리프래쉬 토큰입니다.' 
            },
                HttpStatus.UNAUTHORIZED,
            )
        }
        return "JwtRefreshStrategy 확인"
    }
}
