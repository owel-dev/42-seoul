import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateBanDto } from './dto/create-ban.dto';
import { ResBanDto } from './dto/res-ban.dto';
import { UpdateBanDto } from './dto/update-ban.dto';
import { Ban } from './entities/ban.entity';

@Injectable()
export class BanService {
  constructor(
    @InjectRepository(Ban)
    private banRepository: Repository<Ban>,
    @InjectRepository(User)
    private userRepository: Repository<User>,
  ) {}

  async create(createBanDto: CreateBanDto) {
    // console.log('Ban created');
    const ban1 = await this.userRepository.findOne({
      where: { nickname: createBanDto.player1 },
    });
    const ban2 = await this.userRepository.findOne({
      where: { nickname: createBanDto.player2 },
    });
    if (ban1 === null)
      throw new HttpException(
        {
          statusCode: 'BA02',
          error: `${createBanDto.player1}: Cannot find user`,
        },
        HttpStatus.BAD_REQUEST,
      );
    if (ban2 === null)
      throw new HttpException(
        {
          statusCode: 'BA02',
          error: `${createBanDto.player1}: Cannot find user`,
        },
        HttpStatus.BAD_REQUEST,
      );
    const alreadyBan = await this.banRepository.findOne({
      relations: ['ban_1', 'ban_2'],
      where: {
        ban_1: ban1,
        ban_2: ban2,
      },
    });
    // console.log(alreadyBan);
    if (alreadyBan !== null)
      throw new HttpException(
        { statusCode: 'BA01', error: `Already Banned` },
        HttpStatus.BAD_REQUEST,
      );
    const ban = new Ban();
    ban.ban_1 = ban1;
    ban.ban_2 = ban2;
    return this.banRepository.save(ban);
  }

  async getBanListOne(nickName: string) {
    if (
      (await this.userRepository.findOneBy({ nickname: nickName })) ===
      undefined
    )
      throw new HttpException(
        {
          statusCode: 'BA02',
          error: `${nickName}: Cannot find user`,
        },
        HttpStatus.BAD_REQUEST,
      );
    const banRepo = await this.banRepository.find({
      relations: {
        ban_1: true,
        ban_2: true,
      },
      where: { ban_1: { nickname: nickName } },
    });
    const resBanListDto = banRepo.map((ban, index, array) => {
      const resBanDto = new ResBanDto();
      resBanDto.nickName = ban.ban_2.nickname;
      return resBanDto;
    });
    return { banList: resBanListDto };
  }

  async deleteBan(player1: string, player2: string) {
    // console.log('delete ban');
    const findBan = await this.banRepository.findOne({
      relations: ['ban_1', 'ban_2'],
      where: {
        ban_1: { nickname: player1 },
        ban_2: { nickname: player2 },
      },
    });
    if (findBan === null)
      throw new HttpException(
        { statusCode: 'BD01', error: 'Not Banned' },
        HttpStatus.BAD_REQUEST,
      );
    await this.banRepository.delete(findBan);
  }
}
