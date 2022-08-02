import { Controller, Get, Post, Body, Patch, Param, Delete, Query, HttpCode, UseGuards } from '@nestjs/common';
import { FriendService } from './friend.service';
import { CreateFriendDto } from './dto/create-friend.dto';
import { UpdateFriendDto } from './dto/update-friend.dto';
import { DeleteFriendDto } from './dto/delete-friend.dto';
import { AuthGuard } from '@nestjs/passport';
import { Token } from 'src/auth/auth.decorator';

@Controller('friend')
export class FriendController {
	constructor(private readonly friendService: FriendService) {}

	@Post()
	@UseGuards(AuthGuard('jwt-acess-token'))
	create(@Token() token: string, @Query('user') nickName: string) {
		return this.friendService.create(token, nickName);
	}

	@Get(':nickname')
	@UseGuards(AuthGuard('jwt-acess-token'))
	findOne(@Param('nickname') nickName: string) {
		return this.friendService.getFriendListOne(nickName);
	}

	@Delete()
	@UseGuards(AuthGuard('jwt-acess-token'))
	@HttpCode(204)
	deleteFriend(@Token() token: string, @Query('user') nickName) {
		return this.friendService.deletefriend(token, nickName);
	}
}
