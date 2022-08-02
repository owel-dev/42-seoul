import { Inject, Injectable, UnauthorizedException } from "@nestjs/common";
import { PassportStrategy } from "@nestjs/passport";
import { Repository } from "typeorm";
import {ExtractJwt, Strategy} from "passport-jwt"
import { User } from "src/users/entities/user.entity";
import { InjectRepository } from "@nestjs/typeorm";

@Injectable()
export class JwtStrategy extends PassportStrategy(Strategy){
    constructor(
        @InjectRepository(User)
		private userRepository: Repository<User>
    ){
        super({
            secretOrKey: 'Secret1234',
            jwtFromRequest: ExtractJwt.fromUrlQueryParameter("token")
        })
    }
    async validate(payload) {
        const { intra_id } = payload;
        const user = await this.userRepository.findOneBy({intra_id : intra_id});
        console.log(user);
        console.log("확인");
        //유효1하지 않은 토큰
        //토큰 만효
        //서버오류
        if (user === null) {
            throw new UnauthorizedException();
        }
        return user;
    }
}
