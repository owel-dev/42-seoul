import {
  BadRequestException,
  ForbiddenException,
  forwardRef,
  HttpException,
  HttpStatus,
  Injectable,
  NotFoundException,
} from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { AuthService } from 'src/auth/auth.service';
import { Ban } from 'src/ban/entities/ban.entity';
import { ChatService } from 'src/chat/chat.service';
import { Friend } from 'src/friend/entities/friend.entity';
import { Stat } from 'src/stats/entities/stat.entity';
import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';
import { ResUserModal } from './dto/res-user-modal.dto';
import { ResUserMyPage } from './dto/res-user-mypage.dto';
import { ResUserNavi } from './dto/res-user-navi.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { User } from './entities/user.entity';
import { ConfigService } from '@nestjs/config';

@Injectable()
export class UsersService {
  constructor(
    @InjectRepository(User)
    private userRepository: Repository<User>,
    @InjectRepository(Friend)
    private friendRepository: Repository<Friend>,
    @InjectRepository(Ban)
    private banRepository: Repository<Ban>,
    private readonly authService: AuthService,
    private config: ConfigService,
  ) {}

  async findOneMyPage(token: string, nickName: string) {
    // console.log('user findOneMyPage');
    const reqNick = await this.authService.getUserNickByToken(token);
    const userRepo = await this.userRepository.findOne({
      relations: ['stats', 'friend_1', 'friend_2'],
      where: {
        nickname: nickName,
      },
    });
    if (!userRepo) throw new NotFoundException(`${nickName}: Cannot find user`);
    const resUserMyPage = new ResUserMyPage();
    resUserMyPage.intraId = userRepo.intra_id;
    resUserMyPage.avatar = userRepo.avatar;
    resUserMyPage.nickName = userRepo.nickname;
    resUserMyPage.win = userRepo.stats.win;
    resUserMyPage.lose = userRepo.stats.lose;
    resUserMyPage.winRate = (userRepo.stats.winrate * 100).toFixed() + '%';
    resUserMyPage.isFriend = await this.isFriend(reqNick, userRepo.friend_2);

    return resUserMyPage;
  }

  async findOneModal(token: string, nickName: string) {
    // console.log('user findOneModal');
    const reqNick = await this.authService.getUserNickByToken(token);
    const userRepo = await this.userRepository.findOne({
      relations: ['stats', 'friend_1', 'friend_2', 'ban_1', 'ban_2'],
      where: {
        nickname: nickName,
      },
    });
    if (!userRepo)
      throw new HttpException(
        { statusCode: 'PU01', error: `${nickName}: Cannot find user` },
        HttpStatus.BAD_REQUEST,
      );
    const resUserModal = new ResUserModal();
    resUserModal.nickName = userRepo.nickname;
    resUserModal.win = userRepo.stats.win;
    resUserModal.lose = userRepo.stats.lose;
    resUserModal.winRate = (userRepo.stats.winrate * 100).toFixed() + '%';
    resUserModal.status = userRepo.status;
    resUserModal.channelId = userRepo.channel_id;
    resUserModal.friend = await this.isFriend(reqNick, userRepo.friend_2);
    resUserModal.ban = await this.isBan(reqNick, userRepo.ban_2);
    resUserModal.owner = await this.isOwner(reqNick, userRepo.intra_id);
    resUserModal.admin = await this.isAdmin(reqNick, userRepo.intra_id);
    return resUserModal;
  }

  async findOneNavi(token: string) {
    // console.log('findOneNavi');
    const userNick = await this.authService.getUserNickByToken(token);
    const userRepo = await this.userRepository.findOne({
      where: {
        nickname: userNick,
      },
    });
    if (!userRepo) throw new NotFoundException(`${userNick}: Cannot find user`);
    const resUserNavi = new ResUserNavi();
    resUserNavi.nickName = userRepo.nickname;
    resUserNavi.avatar = userRepo.avatar;
    resUserNavi.isSecondAuth = userRepo.is_second_auth;
    resUserNavi.owner = await this.isOwner(userNick, userRepo.intra_id);
    resUserNavi.admin = await this.isAdmin(userNick, userRepo.intra_id);
    resUserNavi.enable2FA = userRepo.enable2fa;
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

  async isAdmin(requester: string, intraId: string): Promise<boolean> {
    const findUser = await this.userRepository.findOneBy({
      nickname: requester,
    });
    if (!findUser)
      throw new NotFoundException(`${requester}: Cannot find user`);
    return ChatService.channels
      .get(findUser.channel_id)
      ?.adminList.includes(intraId);
  }

  async isOwner(requester: string, intraId: string): Promise<boolean> {
    const findUser = await this.userRepository.findOneBy({
      nickname: requester,
    });
    if (!findUser)
      throw new NotFoundException(`${requester}: Cannot find user`);

    return ChatService.channels.get(findUser.channel_id)?.owner === intraId;
  }

  //   create(createUserDto: CreateUserDto, file: Express.Multer.File) {
  //     return this.saveUser(createUserDto, file);
  //   }

  async update(
    nickName: string,
    updateUserDto: UpdateUserDto,
    file: Express.Multer.File,
  ) {
    if (!nickName)
      throw new ForbiddenException(`${nickName}: nickName cannot be empty`);
    const userRepo = await this.userRepository.findOneBy({
      nickname: nickName,
    });
    const prevAvatar = userRepo.avatar;
    if (userRepo === undefined)
      throw new NotFoundException(`${nickName}: Cannot find user`);

    if (
      updateUserDto.nickName !== undefined &&
      (await this.isNickAvailable(updateUserDto.nickName))
    ) {
      userRepo.nickname = updateUserDto.nickName;
    }
    if (file !== undefined) {
      userRepo.avatar = `https://${this.config.get(
        'BACK_HOST',
      )}:3000/public/avatar/${file.filename}`;
      if (!prevAvatar.includes('https://cdn.intra.42.fr')) {
        const prevFilename = prevAvatar.split('/').pop();
        const prevPath = `${file.destination}/${prevFilename}`;
        this.deleteFile(prevPath);
      }
    }
    if (updateUserDto.enable2FA !== undefined) {
      if (!updateUserDto.enable2FA) {
        userRepo.is_second_auth = true;
      }
      userRepo.enable2fa = updateUserDto.enable2FA;
    }
    await this.userRepository.save(userRepo);
    return userRepo.avatar;
  }

  async initializeStatus() {
    this.userRepository.update(
      {},
      {
        channel_id: '0',
        status: 'offline',
      },
    );
  }

  //   async delete(nickName: string) {
  //     console.log('delete user');
  //     await this.userRepository.delete({ nickname: nickName });
  //   }

  //   private async saveUser(
  //     createUserDto: CreateUserDto,
  //     file: Express.Multer.File,
  //   ) {
  //     const user = new User();
  //     const filePath = `avatar/${file.filename}`;
  //     const ipv4 = await this.getIpAdrress();

  //     user.intra_id = createUserDto.intraId;
  //     user.nickname = createUserDto.nickName;
  //     user.intra_email = createUserDto.intraEmail;
  //     user.avatar = `http://${ipv4}:3000/public/${filePath}`;
  //     user.status = createUserDto.status;
  //     user.channel_id = createUserDto.channelId;
  //     user.stats = new Stat();

  //     return await this.userRepository.save(user);
  //   }

  private async isNickAvailable(nickName: string) {
    const users = await this.userRepository.find({
      where: {
        nickname: nickName,
      },
    });
    if (users.length === 0) {
      return true;
    } else {
      throw new HttpException(
        { statusCode: 'NC01', error: `${nickName}: Nickname already exist` },
        HttpStatus.BAD_REQUEST,
      );
    }
  }

  //   private async getIpAdrress() {
  //     const { networkInterfaces } = require('os');
  //     const nets = networkInterfaces();
  //     const ipv4 = nets['en0'][1]['address'];
  //     return ipv4;
  //   }

  private async deleteFile(path: string) {
    const fs = require('fs');
    fs.unlink(path, (err) => {
      if (err) 
        return;
    });
  }
}
