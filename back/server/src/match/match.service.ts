import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateMatchDto } from './dto/create-match.dto';
import { ResMatchDto } from './dto/res-match.dto';
import { Match } from './entities/match.entity';

@Injectable()
export class MatchService {
  constructor(
    @InjectRepository(Match)
    private matchRepository: Repository<Match>,
    @InjectRepository(User)
    private userRepository: Repository<User>,
  ) {}

  async create(createMatchDto: CreateMatchDto) {
    const player1 = await this.userRepository.findOne({
      where: { nickname: createMatchDto.player1 },
    });
    const player2 = await this.userRepository.findOne({
      where: { nickname: createMatchDto.player2 },
    });

    if (player1 === undefined || player2 === undefined)
      throw new HttpException(
        `${createMatchDto.player1}, ${createMatchDto.player2}: Cannot find user`,
        HttpStatus.BAD_REQUEST,
      );

    if (createMatchDto.score1 > createMatchDto.score2) {
      player1.stats.win++;
      player2.stats.lose++;
    } else {
      player1.stats.lose++;
      player1.stats.win++;
    }
    const match = new Match();
    match.mode = createMatchDto.mode;
    match.score_1 = createMatchDto.score1;
    match.score_2 = createMatchDto.score2;
    match.player_1 = player1;
    match.player_2 = player2;
    return await this.matchRepository.save(match);
  }

  //   findAll() {
  //     return `This action returns all match`;
  //   }

  async getMatchListOne(nickName: string) {
    const user = await this.userRepository.findOneBy({ nickname: nickName });
    if (user === undefined)
      throw new HttpException(
        `${nickName}: Cannot find user`,
        HttpStatus.BAD_REQUEST,
      );
    const matchRepo = await this.matchRepository.find({
      relations: {
        player_1: true,
        player_2: true,
      },
      where: [
        {
          player_1: { nickname: nickName },
        },
        {
          player_2: { nickname: nickName },
        },
      ],
      order: {
        match_id: 'DESC',
      },
    });
    const matchList = matchRepo.map((match, index, array) => {
      const resMatchDto = new ResMatchDto();
      resMatchDto.player1 = match.player_1.nickname;
      resMatchDto.player2 = match.player_2.nickname;
      resMatchDto.score1 = match.score_1;
      resMatchDto.score2 = match.score_2;
      resMatchDto.mode = match.mode;
      return resMatchDto;
    });
    return { matchList: matchList };
  }

  //   update(id: number, updateMatchDto: UpdateMatchDto) {
  //     return `This action updates a #${id} match`;
  //   }

  //   remove(id: number) {
  //     return `This action removes a #${id} match`;
  //   }
}
