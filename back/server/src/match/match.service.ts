import { Inject, Injectable } from '@nestjs/common';
import { User } from 'src/users/entities/user.entity';
import { DataSource, Repository } from 'typeorm';
import { CreateMatchDto } from './dto/create-match.dto';
import { UpdateMatchDto } from './dto/update-match.dto';
import { Match } from './entities/match.entity';

@Injectable()
export class MatchService {
	constructor(
		@Inject('MATCH_REPOSITORY')
		private matchRepository: Repository<Match>,
	) { }

  create(createMatchDto: CreateMatchDto) {
	const user1 = new User();
	user1.intra_id = createMatchDto.player1;
    // return 'This action adds a new match';
  }

//   findAll() {
//     return `This action returns all match`;
//   }

//   findOne(id: number) {
//     return `This action returns a #${id} match`;
//   }

//   update(id: number, updateMatchDto: UpdateMatchDto) {
//     return `This action updates a #${id} match`;
//   }

//   remove(id: number) {
//     return `This action removes a #${id} match`;
//   }
}
