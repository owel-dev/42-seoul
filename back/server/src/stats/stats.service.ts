import {
  HttpException,
  HttpStatus,
  Inject,
  Injectable,
  Res,
} from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { ResRankDto } from './dto/res-rank.dto';
import { UpdateStatDto } from './dto/update-stat.dto';
import { Stat } from './entities/stat.entity';

@Injectable()
export class StatsService {
  constructor(
    @InjectRepository(Stat)
    private statRepository: Repository<Stat>,
    @InjectRepository(User)
    private userRepository: Repository<User>,
  ) {}

  async getRanking(numUser: number) {
    const rankRepo = await this.statRepository.find({
      relations: ['user'],
      order: {
        win: 'DESC',
        winrate: 'DESC',
      },
      take: numUser,
    });
    const resRankDto = new ResRankDto();
    resRankDto.rankingArr = rankRepo;
    return resRankDto;
  }

  async update(nickName: string, updateStatDto: UpdateStatDto) {
    const user = await this.userRepository.findOne({
      where: { nickname: nickName },
    });
    if (user === undefined)
      throw new HttpException(
        `${nickName}: Cannot find user`,
        HttpStatus.BAD_REQUEST,
      );

    const statUpdate = await this.statRepository.findOne({
      relations: ['user'],
      where: {
        user: user,
      },
    });
    statUpdate.win = updateStatDto.win;
    statUpdate.lose = updateStatDto.lose;
    statUpdate.winrate =
      +updateStatDto.win / (+updateStatDto.win + +updateStatDto.lose);
    return await this.statRepository.save(statUpdate);
  }

  //   remove(id: number) {
  //     return `This action removes a #${id} stat`;
  //   }
}
