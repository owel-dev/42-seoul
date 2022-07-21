import { HttpException, HttpStatus, Inject, Injectable } from '@nestjs/common';
import { AuthService } from 'src/auth/auth.service';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateFriendDto } from './dto/create-friend.dto';
import { DeleteFriendDto } from './dto/delete-friend.dto';
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
		private readonly authService: AuthService,
	) { }

	async create(token: string, nickName: string) {
		console.log("Friend created");
		const reqUser = await this.authService.getUserNickByToken(token);
		const friend1 = await this.userRepository.findOne({
			where: { nickname: reqUser },
		})
		const friend2 = await this.userRepository.findOne({
			where: { nickname: nickName },
		});
		if (friend1 === null)
			throw new HttpException(`${reqUser}: Cannot find user`, HttpStatus.BAD_REQUEST);
		if (friend2 === null)
			throw new HttpException(`${nickName}: Cannot find user`, HttpStatus.BAD_REQUEST);
		
		const alreadyFriend = await this.friendRepository.findOne({
			relations: ["friend_1", 'friend_2'],
			where: {
				friend_1: friend1,
				friend_2: friend2,
			},
		});
		if (alreadyFriend !== null)
			throw new HttpException(`Already friend`, HttpStatus.BAD_REQUEST);
		const friend = new Friend();
		friend.friend_1 = friend1;
		friend.friend_2 = friend2;
		return (this.friendRepository.save(friend));
	}

	async getFriendListOne(nickName: string) {
		if (await this.userRepository.findOneBy({ nickname: nickName }) === undefined)
			throw new HttpException(`${nickName}: Cannot find user`, HttpStatus.BAD_REQUEST);
		const friendRepo = await this.friendRepository.find({
			relations: {
				friend_1: true,
				friend_2: true,
			},
			where: { friend_1: { nickname: nickName } },
		});
		let resFrinedListDto = new ResFriendListDto();
		resFrinedListDto.friendToResFriendArr(friendRepo);
		return resFrinedListDto;
	}

	async deletefriend(token: string, nickName: string) {
		console.log("delete friend");
		const reqUser = await this.authService.getUserNickByToken(token);
		const findFriend = await this.friendRepository.findOne({
			relations: ["friend_1", 'friend_2'],
			where: {
				friend_1: { nickname: reqUser },
				friend_2: { nickname: nickName },
			}
		});
		if (findFriend === null)
			throw new HttpException("Not friend", HttpStatus.BAD_REQUEST);
		await this.friendRepository.delete(findFriend);
	}
}
