import { Inject, Injectable } from '@nestjs/common';
import { Stat } from 'src/stats/entities/stat.entity';
import { Repository } from 'typeorm';
import { CreateUserDto } from './dto/create-user.dto';
import { ResUserMyPage } from './dto/res-user-mypage.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { User } from './entities/user.entity';

@Injectable()
export class UsersService {
	constructor(
		@Inject('USER_REPOSITORY')
		private userRepository: Repository<User>,
	) { }

	private async saveUser(createUserDto: CreateUserDto)
	{
		const user = new User();
		user.intra_id = createUserDto.intraId;
		user.nickname = createUserDto.nickName;
		user.intra_email = createUserDto.intraEmail;
		user.avatar = createUserDto.avatar;
		user.status = createUserDto.status;
		user.role = createUserDto.role;
		user.channel_id = createUserDto.channelId;

		user.stats = new Stat();
		await this.userRepository.save(user);
	}

	async findOneMyPage(intraId : string)
	{
		const userRepo = await this.userRepository.findOne({
			relations: ["stats"],
			where: {
				intra_id: intraId,
			}

		});
		return (new ResUserMyPage(userRepo));
	}

  create(createUserDto: CreateUserDto) {
    return this.saveUser(createUserDto);
  }

//   findAll() {
//     return `This action returns all users`;
//   }

//   findOne(id: number) {
//     return `This action returns a #${id} user`;
//   }

//   update(id: number, updateUserDto: UpdateUserDto) {
//     return `This action updates a #${id} user`;
//   }

//   remove(id: number) {
//     return `This action removes a #${id} user`;
//   }
}
