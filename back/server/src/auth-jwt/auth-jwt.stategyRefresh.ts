import { Injectable } from "@nestjs/common";
import { PassportStrategy } from "@nestjs/passport";
import { ExtractJwt, Strategy } from "passport-jwt";

@Injectable()
export class JwtRefreshStrategy extends PassportStrategy(Strategy, 'jwt-refresh-token') {
    constructor() {
        super({
            secretOrKey: 'RefreshJwt',
            jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
            ignoreExpiration: false
        })
    }

    async validate(payload: any)
    {
        // console.log("JwtRefreshStrategy");
        //리프래쉬 토큰이 만료되면? 
        //에러코드 발송
        //클라이언트 측에서 로그인페이지로 리다이렉트 시켜줘야함.
        
        // console.log("refreshJwt ");
        // console.log(payload);
        return "(refreshJwt 확인)"
    }
}
