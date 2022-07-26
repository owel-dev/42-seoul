import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { AuthService } from 'src/auth/auth.service';
import { Ban } from 'src/ban/entities/ban.entity';
import { Friend } from 'src/friend/entities/friend.entity';
import { Stat } from 'src/stats/entities/stat.entity';
import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';
import { ResUserModal } from './dto/res-user-modal.dto';
import { ResUserMyPage } from './dto/res-user-mypage.dto';
import { ResUserNavi } from './dto/res-user-navi.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { User } from './entities/user.entity';

@Injectable()
export class UsersService {
  constructor(
    @Inject('USER_REPOSITORY')
    private userRepository: Repository<User>,
    @Inject('FRIEND_REPOSITORY')
    private friendRepository: Repository<Friend>,
    @Inject('BAN_REPOSITORY')
    private banRepository: Repository<Ban>,
    private readonly authService: AuthService,
  ) {}

  async findOneMyPage(nickName: string) {
    console.log('user findOneMyPage');
    const userRepo = await this.userRepository.findOne({
      relations: ['stats'],
      where: {
        nickname: nickName,
      },
    });
    if (userRepo == undefined)
      throw new HttpException(
        `${nickName}: Cannot find user`,
        HttpStatus.BAD_REQUEST,
      );
    return new ResUserMyPage(userRepo);
  }

  async findOneModal(token: string, nickName: string) {
    console.log('user findOneModal');
    const reqNick = await this.authService.getUserNickByToken(token);
    const userRepo = await this.userRepository.findOne({
      relations: ['stats', 'friend_1', 'friend_2', 'ban_1', 'ban_2'],
      where: {
        nickname: nickName,
      },
    });
    console.log(userRepo);
    if (userRepo == undefined)
      throw new HttpException(
        `${nickName}: Cannot find user`,
        HttpStatus.BAD_REQUEST,
      );
    const resUserModal = new ResUserModal(userRepo);
    resUserModal.setFriend = await this.isFriend(reqNick, userRepo.friend_2);
    resUserModal.setBan = await this.isBan(reqNick, userRepo.ban_2);
    console.log(resUserModal.friend);
    console.log(resUserModal.ban);
    return resUserModal;
  }

  async findOneNavi(token: string) {
    console.log('findOneNavi');
    const userNick = await this.authService.getUserNickByToken(token);
    console.log('userNick', userNick);
    const userRepo = await this.userRepository.findOne({
      where: {
        nickname: userNick,
      },
    });
    console.log('userRepo', userRepo);
    const resUserNavi = new ResUserNavi(userRepo);
    return resUserNavi;
  }

  async isFriend(requester: string, friendList: Friend[]): Promise<boolean> {
    for (let i = 0; i < friendList.length; i++) {
      const friend = await this.friendRepository.findOne({
        relations: ['friend_1', 'friend_2'],
        where: { friend_id: friendList[i].friend_id },
      });
      if (friend.friend_1.nickname == requester) return true;
    }
    return false;
  }

  async isBan(requester: string, banList: Ban[]): Promise<boolean> {
    for (let i = 0; i < banList.length; i++) {
      const ban = await this.banRepository.findOne({
        relations: ['ban_1', 'ban_2'],
        where: { ban_id: banList[i].ban_id },
      });
      if (ban.ban_1.nickname == requester) return true;
    }
    return false;
  }

  create(createUserDto: CreateUserDto, file: Express.Multer.File) {
    return this.saveUser(createUserDto, file);
  }

  async update(
    nickName: string,
    updateUserDto: UpdateUserDto,
    file: Express.Multer.File,
  ) {
    if (
      (await this.userRepository.findOneBy({ nickname: nickName })) == undefined
    )
      throw new HttpException(
        `${nickName}: Cannot find user`,
        HttpStatus.BAD_REQUEST,
      );
    const ipv4 = await this.getIpAdrress();
    if (updateUserDto.nickName !== undefined) {
      if (await this.isNickAvailable(updateUserDto.nickName)) {
        console.log('nickname updated');
        this.userRepository.update(
          { nickname: nickName },
          { nickname: updateUserDto.nickName },
        );
      }
    }
    if (file !== undefined) {
      console.log('avatar updated');
      this.userRepository.update(nickName, {
        avatar: `http://${ipv4}:3000/public/avatar/${file.filename}`,
      });
    }
    return `update`;
  }

  async delete(nickName: string) {
    console.log('delete user');
    await this.userRepository.delete({ nickname: nickName });
  }

  private async saveUser(
    createUserDto: CreateUserDto,
    file: Express.Multer.File,
  ) {
    const user = new User();
    const filePath = `avatar/${file.filename}`;
    const ipv4 = await this.getIpAdrress();

    user.intra_id = createUserDto.intraId;
    user.nickname = createUserDto.nickName;
    user.intra_email = createUserDto.intraEmail;
    user.avatar = `http://${ipv4}:3000/public/${filePath}`;
    user.status = createUserDto.status;
    user.channel_id = createUserDto.channelId;
    user.stats = new Stat();

    return await this.userRepository.save(user);
  }

  private async isNickAvailable(nickName: string) {
    const users = await this.userRepository.find({
      where: {
        nickname: nickName,
      },
    });
    console.log(nickName);
    console.log(users);
    if (users.length === 0) {
      return true;
    } else {
      throw new HttpException(
        `${nickName}: Nickname already exist`,
        HttpStatus.FORBIDDEN,
      );
    }
  }

  private async getIpAdrress() {
    const { networkInterfaces } = require('os');
    const nets = networkInterfaces();
    const ipv4 = nets['en0'][1]['address'];
    return ipv4;
  }
}
