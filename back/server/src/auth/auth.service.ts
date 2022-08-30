import {
  HttpException,
  HttpStatus,
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
import { AuthJwtService } from 'src/auth-jwt/auth-jwt.service';
import { ConfigService } from '@nestjs/config';

const hashedCodes = {};

@Injectable()
export class AuthService {
  constructor(
    @InjectRepository(User)
    private userRepository: Repository<User>,
    private mailerService: MailerService,
    private config: ConfigService,
    private authJwtService: AuthJwtService,
  ) {}

  async getAccessToken(code: string): Promise<string> {
    // console.log('code=', code);
    const payload = {
      grant_type: 'authorization_code',
      client_id: this.config.get('INTRA_UID'),
      client_secret: this.config.get('INTRA_SECRET'),
      redirect_uri: this.config.get('REDIRECT_URI'),
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
        // console.log(err);
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
          // console.log('get /v2/me error');
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
        status: 'offline',
        channel_id: '0',
        socket_id: null,
        stats: new Stat(),
        is_second_auth: false,
      };
      user = await this.userRepository.save(userEntity);
    }
    if (user.enable2fa) {
      user.is_second_auth = false;
      await this.userRepository.save(user);
    }

    const jwtToken = await this.login(user.intra_id);
    response.cookie('accessToken', jwtToken.accessToken, {
      sameSite: 'lax',
      httpOnly: true,
      path: '/',
      maxAge: 24 * 60 * 60 * 1000,
    });
    response.cookie('refreshToken', jwtToken.refreshToken, {
      sameSite: 'lax',
      httpOnly: true,
      path: '/',
      maxAge: 24 * 60 * 60 * 1000,
    });
    response.redirect(
      302,
      `https://${this.config.get('FRONT_HOST')}:${this.config.get(
        'FRONT_PORT',
      )}?accessToken=${jwtToken.accessToken}&refreshToken=${
        jwtToken.refreshToken
      }`
    );
    return response;
  }

  async getUserNickByToken(token: string): Promise<string> {
    const user = await this.authJwtService.jwtVerify(token);
    // console.log('+++getUserNickByToken', user);
    if (!user) return undefined;
    const userFind = await this.userRepository.findOneBy({
      intra_id: user.intra_id,
    });
    if (!userFind) {
      return undefined;
    }
    return userFind.nickname;
  }

  async sendEmail(id: string): Promise<void> {
    if (hashedCodes[id]) return;

    const code = Math.floor(1000 + Math.random() * 9000).toString();
    const salt = await bcrypt.genSalt();
    const hashedCode = await bcrypt.hash(code, salt);

    hashedCodes[id] = hashedCode.toString();

    const userRow = await this.userRepository.findOneBy({nickname: id});
    if (userRow.intra_email === undefined)
      return ;
    await this.mailerService.sendMail({
      to: userRow.intra_email,
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
    const resDto = new ResUserNavi();
    resDto.nickName = userFind.nickname;
    resDto.avatar = userFind.avatar;
    resDto.isSecondAuth = userFind.is_second_auth;
    resDto.enable2FA = userFind.enable2fa;
    return resDto;
  }

  async login(intra_id: string) {
    const accessToken = await this.authJwtService.createAccessJwt(intra_id);
    const refreshToken = await this.authJwtService.createRefreshJwt(intra_id);

    return {
      accessToken: accessToken,
      refreshToken: refreshToken,
    };
  }

  async logout() {
    //소켓 연결 끊기
  }

  async fetchData(url) {
    try {
      const res = await axios.get(url);
      if (res.status !== 200) {
        throw new Error('Network response was not ok');
      }
      return res.data;
    } catch (error) {
      console.error('Unable to fetch data:', error);
    }
  }

  pickRandom(list) {
    return list[Math.floor(Math.random() * list.length)];
  }

  async generateName() {
    try {
      const randomNameList = await this.fetchData(
        `https://www.randomlists.com/data/names-surnames.json`,
      );
      const randomName = this.pickRandom(randomNameList.data);
      return randomName;
    } catch (error) {
      console.error('Unable to generate name:', error);
    }
  }

  async testLogin(@Res() response: Response) {
    // console.log('testLogin-service');
    let userEntity = new User();
    let randomName = await this.generateName();
    userEntity = {
      intra_id: randomName,
      nickname: randomName,
      intra_email: 'mail@test.com',
      avatar: '',
      status: 'offline',
      channel_id: '0',
      socket_id: null,
      stats: new Stat(),
      is_second_auth: true,
    };
    await this.userRepository.save(userEntity);
    const jwtToken = await this.login(userEntity.intra_id);
    response.cookie('accessToken', jwtToken.accessToken, {
      sameSite: 'lax',
      httpOnly: true,
      path: '/',
      maxAge: 24 * 60 * 60 * 1000,
    });
    response.cookie('refreshToken', jwtToken.refreshToken, {
      sameSite: 'lax',
      httpOnly: true,
      path: '/',
      maxAge: 24 * 60 * 60 * 1000,
    });
    response.redirect(
      `https://${this.config.get('FRONT_HOST')}:${this.config.get(
        'FRONT_PORT',
      )}?accessToken=${jwtToken.accessToken}&refreshToken=${
        jwtToken.refreshToken
      }`,
      302,
    );
    return response;
  }
}
