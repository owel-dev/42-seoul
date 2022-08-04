import { Injectable, UnauthorizedException } from "@nestjs/common";
import { PassportStrategy } from "@nestjs/passport";
import { Repository } from "typeorm";
import { ExtractJwt, Strategy } from "passport-jwt"
import { User } from "src/users/entities/user.entity";
import { InjectRepository } from "@nestjs/typeorm";

@Injectable()
export class JwtAccessStrategy extends PassportStrategy(Strategy, 'jwt-access-token') {
    constructor(
        @InjectRepository(User)
        private userRepository: Repository<User>
    ) {
        super({
            secretOrKey: 'accessJwt',
            jwtFromRequest: ExtractJwt.fromAuthHeaderAsBearerToken(),
            ignoreExpiration: false
        })
    }
    async validate(payload: any) {
        const { intra_id } = payload;
        const user = await this.userRepository.findOneBy({ intra_id: intra_id });
        // console.log("JwtaccessStrategy 확인");
        // console.log(payload);
        return "JwtaccessStrategy 확인";
    }
}
