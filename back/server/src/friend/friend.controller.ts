import { Controller, Get, Post, Body, Patch, Param, Delete, Query, HttpCode } from '@nestjs/common';
import { FriendService } from './friend.service';
import { CreateFriendDto } from './dto/create-friend.dto';
import { UpdateFriendDto } from './dto/update-friend.dto';
import { DeleteFriendDto } from './dto/delete-friend.dto';

@Controller('friend')
export class FriendController {
	constructor(private readonly friendService: FriendService) {}

	@Post()
	create(@Body() createFriendDto: CreateFriendDto) {
		return this.friendService.create(createFriendDto);
	}

	@Get(':nickname')
	findOne(@Param('nickname') nickName: string) {
		return this.friendService.getFriendListOne(nickName);
	}

	@Delete()
	@HttpCode(204)
	deleteFriend(@Query('player1') player1: string, @Query('player2') player2) {
		return this.friendService.deletefriend(player1, player2);
	}
}
