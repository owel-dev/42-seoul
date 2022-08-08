import {
  BadRequestException,
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
    const rankList = rankRepo.map((stat, index, array) => {
      const resRankDto = new ResRankDto();
      const rank =
        array.filter(
          (iter) =>
            iter.win > stat.win ||
            (iter.win === stat.win && iter.winrate > stat.winrate),
        ).length + 1;
      resRankDto.rank = rank;
      resRankDto.nickName = stat.user.nickname;
      resRankDto.win = stat.win;
      resRankDto.lose = stat.lose;
      resRankDto.winRate = (stat.winrate * 100).toFixed() + '%';
      return resRankDto;
    });
    return { ranking: rankList };
  }

  //   async update(nickName: string, updateStatDto: UpdateStatDto) {
  //     const user = await this.userRepository.findOne({
  //       where: { nickname: nickName },
  //     });
  //     if (user === undefined)
  //       throw new BadRequestException(`${nickName}: Cannot find user`);

  //     const statUpdate = await this.statRepository.findOne({
  //       relations: ['user'],
  //       where: {
  //         user: user,
  //       },
  //     });
  //     statUpdate.win = updateStatDto.win;
  //     statUpdate.lose = updateStatDto.lose;
  //     statUpdate.winrate =
  //       +updateStatDto.win / (+updateStatDto.win + +updateStatDto.lose);
  //     return await this.statRepository.save(statUpdate);
  //   }
}
