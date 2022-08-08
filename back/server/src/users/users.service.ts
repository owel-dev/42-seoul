import {
  BadRequestException,
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
  ) {}

  async findOneMyPage(nickName: string) {
    // console.log('user findOneMyPage');
    const userRepo = await this.userRepository.findOne({
      relations: ['stats'],
      where: {
        nickname: nickName,
      },
    });
    if (!userRepo) throw new NotFoundException(`${nickName}: Cannot find user`);
    return new ResUserMyPage(userRepo);
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
    const resUserModal = new ResUserModal(userRepo);
    resUserModal.setFriend = await this.isFriend(reqNick, userRepo.friend_2);
    resUserModal.setBan = await this.isBan(reqNick, userRepo.ban_2);
    resUserModal.setAdmin = await this.isAdmin(reqNick);
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

  async isAdmin(requester: string): Promise<boolean> {
    const findUser = await this.userRepository.findOneBy({
      nickname: requester,
    });
    if (!findUser)
      throw new NotFoundException(`${requester}: Cannot find user`);
    const curChannel = ChatService.users.find(
      (user) => user.intraId === findUser.intra_id,
    ).curChannel;
    return ChatService.channels.get(curChannel).admin === findUser.intra_id;
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
      throw new NotFoundException(`${nickName}: Cannot find user`);
    const ipv4 = await this.getIpAdrress();
    if (updateUserDto.nickName !== undefined) {
      if (await this.isNickAvailable(updateUserDto.nickName)) {
        this.userRepository.update(
          { nickname: nickName },
          { nickname: updateUserDto.nickName },
        );
      }
    }
    if (file !== undefined) {
      this.userRepository.update(
        { nickname: nickName },
        {
          avatar: `http://${ipv4}:3000/public/avatar/${file.filename}`,
        },
      );
      return `http://${ipv4}:3000/public/avatar/${file.filename}`;
    }
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
    if (users.length === 0) {
      return true;
    } else {
      throw new HttpException(
        { statusCode: 'NC01', error: `${nickName}: Nickname already exist` },
        HttpStatus.BAD_REQUEST,
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
