import { Inject, Injectable } from '@nestjs/common';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateMatchDto } from './dto/create-match.dto';
import { ResMatchDto } from './dto/res-match.dto';
import { Match } from './entities/match.entity';

@Injectable()
export class MatchService {
	constructor(
		@Inject('MATCH_REPOSITORY')
		private matchRepository: Repository<Match>,
		@Inject('USER_REPOSITORY')
		private userRepository: Repository<User>,

	) { }

	async create(createMatchDto: CreateMatchDto) {
		const player1 = await this.userRepository.findOne({
			where: { intra_id: createMatchDto.player1 },
		});
		const player2 = await this.userRepository.findOne({
			where: { intra_id: createMatchDto.player2 },
		});

		const match = new Match();
		match.mode = "default";
		match.score_1 = createMatchDto.score1;
		match.score_2 = createMatchDto.score2;
		match.player_1 = player1;
		match.player_2 = player2;
		return await this.matchRepository.save(match);
	}

//   findAll() {
//     return `This action returns all match`;
//   }

	async getMatchListOne(intraId: string) {
		const matchRepo = await this.matchRepository.find({
			relations: {
				player_1: true,
				player_2: true,
			},
			where: [
				{
					player_1: { intra_id: intraId }
				},
				{
					player_2: { intra_id: intraId }
				},
			],
			order: {
				match_id: "DESC",
			}
		});
		let resMatchDto = new ResMatchDto();
		resMatchDto.matchArr = matchRepo;
		return resMatchDto;
	}

//   update(id: number, updateMatchDto: UpdateMatchDto) {
//     return `This action updates a #${id} match`;
//   }

//   remove(id: number) {
//     return `This action removes a #${id} match`;
//   }
}
