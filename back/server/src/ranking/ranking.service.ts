import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Stat } from 'src/stats/entities/stat.entity';
import { Repository } from 'typeorm';
import { ResRankDto } from './dto/res-rank.dto';

@Injectable()
export class RankingService {
	constructor(
		@InjectRepository(Stat)
		private statRepository: Repository<Stat>,
	) { }

	async getRanking(numUser: number) {
		const rankRepo = await this.statRepository.find({
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
}
