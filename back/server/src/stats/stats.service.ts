import { Inject, Injectable, Res } from '@nestjs/common';
import { Repository } from 'typeorm';
import { CreateStatDto } from './dto/create-stat.dto';
import { ResRankDto } from './dto/res-rank.dto';
import { ResStatDto } from './dto/res-stat.dto';
import { UpdateStatDto } from './dto/update-stat.dto';
import { Stat } from './entities/stat.entity';

@Injectable()
export class StatsService {
	constructor(
		@Inject('STAT_REPOSITORY')
		private statRepository: Repository<Stat>,
	) { }

	async getRanking(numUser: number) {
		const rankRepo = await this.statRepository.find({
			relations: ["user"],
			order: {
				win: "DESC",
				winrate: "DESC",
			},
			take: numUser,
		});
		let	resRankDto = new ResRankDto();
		resRankDto.rankingArr = rankRepo;
		return resRankDto;
	}

//   findAll() {
//     return `This action returns all stats`;
//   }

  async update(id: string, updateStatDto: UpdateStatDto) {
	const statUpdate = await this.statRepository.findOneBy({
		intra_id: id,
	})
	statUpdate.win = updateStatDto.win;
	statUpdate.lose = updateStatDto.lose;
	statUpdate.winrate = +updateStatDto.win / (+updateStatDto.win + +updateStatDto.lose);
	return await this.statRepository.save(statUpdate);

  }

//   remove(id: number) {
//     return `This action removes a #${id} stat`;
//   }
}
