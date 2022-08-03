import {
  BadRequestException,
  HttpException,
  HttpStatus,
  Inject,
  Injectable,
  NotFoundException,
  Res,
} from '@nestjs/common';
import axios from 'axios';
import { Response } from 'express';
import { Stat } from 'src/stats/entities/stat.entity';
import { CreateUserDto } from 'src/users/dto/create-user.dto';
import { Repository } from 'typeorm';
import { User } from 'src/users/entities/user.entity';
import * as bcrypt from 'bcryptjs';
import { MailerService } from '@nestjs-modules/mailer';
import { ResUserNavi } from 'src/users/dto/res-user-navi.dto';
import { InjectRepository } from '@nestjs/typeorm';

const hashedCodes = {};

@Injectable()
export class AuthService {
  constructor(
    @InjectRepository(User)
    private userRepository: Repository<User>,
    private mailerService: MailerService,
  ) {}

  static tokens = new Map();

  async getAccessToken(code: string): Promise<string> {
    // console.log('code=', code);
    const payload = {
      grant_type: 'authorization_code',
      client_id:
        '10fd003cd72e573d39cefc1302e9a5c3a9722ad06f7bffe91bf3b3587ace5036',
      client_secret:
        '813cf74e92c49fd3c4afadf409bd6eb818fe985a11aefbfb4579bfcf0c032d96',
      redirect_uri: 'http://10.19.236.57:3000/oauth/login',
      code,
    };

    let ret: string;
    await axios
      .post('https://api.intra.42.fr/oauth/token', JSON.stringify(payload), {
        headers: {
          'Content-Type': 'application/json',
        },
      })
      .then((res) => {
        ret = res.data.access_token;
      })
      .catch((err) => {
        console.log(err);
      });
    return ret;
  }

  async getUserData(code: string): Promise<CreateUserDto> {
    let access_token: string;
    let userData: CreateUserDto;
    access_token = await this.getAccessToken(code);
    if (access_token) {
      await axios
        .get('https://api.intra.42.fr/v2/me', {
          headers: {
            Authorization: `Bearer ${access_token}`,
            'content-type': 'application/json',
          },
        })
        .then((res) => {
          const {
            email: intraEmail,
            login: intraId,
            image_url: avatar,
          } = res.data;
          userData = {
            intraId,
            nickName: intraId,
            intraEmail,
            avatar,
            access_token: access_token,
          };
        })
        .catch((res) => {
          console.log('get /v2/me error');
        });
    }
    return userData;
  }

  async saveAccessToken(@Res() response: Response, code: string) {
    // console.log('saveAccessToken');
    const newUser: CreateUserDto = await this.getUserData(code);
    // console.log(newUser);
    if (!newUser) {
      throw new HttpException('Invalid User', HttpStatus.BAD_REQUEST);
    }
    let user = await this.userRepository.findOneBy({
      intra_id: newUser.intraId,
    });
    if (!user) {
      let userEntity = new User();
      userEntity = {
        intra_id: newUser.intraId,
        nickname: newUser.nickName,
        intra_email: newUser.intraEmail,
        avatar: newUser.avatar,
        status: 'online',
        channel_id: '0',
        socket_id: null,
        stats: new Stat(),
        is_second_auth: false,
      };
      user = await this.userRepository.save(userEntity);
      console.log(user);
    }
    AuthService.tokens.set(newUser.access_token, user.intra_id);
    return response.redirect(
      'http://10.19.233.86:3000' + '?token=' + newUser.access_token,
    );
  }

  async getUserNickByToken(token: string): Promise<string> {
    const user = AuthService.tokens.get(token);
    console.log('@@@@ token: ', token);
    console.log('@@@@ user: ', user);
    if (!user) {
      return undefined;
    }
    const userFind = await this.userRepository.findOne({
      where: {
        nickname: user,
      },
    });

    if (!userFind) {
      return undefined;
    }
    console.log('.nickname: ', userFind.nickname);
    return userFind.nickname;
  }

  async sendEmail(id: string, email: string): Promise<void> {
    if (hashedCodes[id]) return;

    const code = Math.floor(1000 + Math.random() * 9000).toString();
    const salt = await bcrypt.genSalt();
    const hashedCode = await bcrypt.hash(code, salt);

    hashedCodes[id] = hashedCode.toString();

    await this.mailerService.sendMail({
      to: email,
      from: 'mailer_ulee@naver.com',
      subject: '2차 인증 코드입니다.',
      text: hashedCode,
    });
  }

  async validEmail(id: string, code: string): Promise<ResUserNavi> {
    const userFind = await this.userRepository.findOneBy({ intra_id: id });
    if (!userFind) throw new NotFoundException('잘못된 id 입니다.');

    if (hashedCodes[id] === code) {
      userFind.is_second_auth = true;
      await this.userRepository.save(userFind);
      delete hashedCodes[id];
    } else {
      throw new HttpException(
        { statusCode: 'SC01', error: '잘못된 코드입니다.' },
        HttpStatus.BAD_REQUEST,
      );
    }
    const resDto = new ResUserNavi(userFind);
    return resDto;
  }
}
