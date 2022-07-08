import { Injectable, Res } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { CreateStatDto } from './dto/create-stat.dto';
import { ResRankDto } from './dto/res-rank.dto';
import { ResStatDto } from './dto/res-stat.dto';
import { UpdateStatDto } from './dto/update-stat.dto';
import { Stat } from './entities/stat.entity';

@Injectable()
export class StatsService {
	constructor(
		@InjectRepository(Stat)
		private statRepository: Repository<Stat>,
	) { }

	private async saveStat(intraId: string, win: number, lose: number, winrate: number)
	{
		const stat = new Stat();
		stat.intra_id = intraId;
		stat.win = win;
		stat.lose = lose;
		stat.winrate = winrate;
		await this.statRepository.save(stat);
	}

	create(createStatDto: CreateStatDto) {
		let win : number = createStatDto.win;
		let lose : number = createStatDto.lose;
		let winrate : number = +win / (+win + +lose);
		return this.saveStat(createStatDto.intraId, createStatDto.win, createStatDto.lose, winrate);
	}

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

	async findOne(intraId : string) {
		const statRepo = await this.statRepository.findOneBy({
			intra_id: intraId,
		});
		let resStatDto = new ResStatDto(statRepo);
		return resStatDto;
	}

//   findAll() {
//     return `This action returns all stats`;
//   }

//   update(id: number, updateStatDto: UpdateStatDto) {
//     return `This action updates a #${id} stat`;
//   }

//   remove(id: number) {
//     return `This action removes a #${id} stat`;
//   }
}
