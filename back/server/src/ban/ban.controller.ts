import { Controller, Get, Post, Body, Patch, Param, Delete, Query, HttpCode, UseGuards } from '@nestjs/common';
import { AuthGuard } from 'src/auth/auth.guard';
import { BanService } from './ban.service';
import { CreateBanDto } from './dto/create-ban.dto';
import { UpdateBanDto } from './dto/update-ban.dto';

@Controller('ban')
export class BanController {
  constructor(private readonly banService: BanService) {}

	@Post()
	@UseGuards(AuthGuard)
	create(@Body() createBanDto: CreateBanDto) {
		return this.banService.create(createBanDto);
	}

	@Get(':nickname')
	@UseGuards(AuthGuard)
	findOne(@Param('nickname') nickName: string) {
		return this.banService.getBanListOne(nickName);
	}

	@Delete()
	@UseGuards(AuthGuard)
	@HttpCode(204)
	deleteBan(@Query('player1') player1: string, @Query('player2') player2) {
		return this.banService.deleteBan(player1, player2);
	}
}
