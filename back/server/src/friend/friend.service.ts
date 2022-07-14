import { Inject, Injectable } from '@nestjs/common';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateFriendDto } from './dto/create-friend.dto';
import { ResFriendListDto } from './dto/res-friend.dto';
import { UpdateFriendDto } from './dto/update-friend.dto';
import { Friend } from './entities/friend.entity';

@Injectable()
export class FriendService {
	constructor(
		@Inject('FRIEND_REPOSITORY')
		private friendRepository: Repository<Friend>,
		@Inject('USER_REPOSITORY')
		private userRepository: Repository<User>,

	) { }
	async create(createFriendDto: CreateFriendDto) {
		console.log(createFriendDto);
		const friend1 = await this.userRepository.findOne({
			where: { intra_id: createFriendDto.friend1 },
		})
		const friend2 = await this.userRepository.findOne({
			where: { intra_id: createFriendDto.friend2 },
		});
		const friend = new Friend();
		friend.status = createFriendDto.status;
		friend.friend_1 = friend1;
		friend.friend_2 = friend2;
		return (this.friendRepository.save(friend));
	}

	async getFriendListOne(intraId: string) {
		const friendRepo = await this.friendRepository.find({
			relations: {
				friend_1: true,
				friend_2: true,
			},
			where: [
				{
					friend_1: { intra_id: intraId },
					status: "accept"
				},
				{
					friend_2: { intra_id: intraId },
					status: "accept"
				},
			],
		});
		let resFrinedListDto = new ResFriendListDto();
		resFrinedListDto.friendToResFriendArr(friendRepo, intraId);
		return resFrinedListDto;
	}
}
