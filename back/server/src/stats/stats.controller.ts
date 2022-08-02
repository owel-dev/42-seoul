import { Controller, Get, Post, Body, Patch, Param, Delete, Query, UseGuards } from '@nestjs/common';
import { StatsService } from './stats.service';
import { UpdateStatDto } from './dto/update-stat.dto';
import { IsInt, IsNumber, IsOptional, Min } from 'class-validator';
import { Type } from 'class-transformer';
import { AuthGuard } from '@nestjs/passport';

class GetRankingQuery
{
	@IsOptional()
	@Type(() => Number)
	@IsInt()
	@Min(1)
	n : number;
}

@Controller('stat')
export class StatsController {
  constructor(private readonly statsService: StatsService) {}

	@Get()
	@UseGuards(AuthGuard('jwt-acess-token'))
	getRanking(@Query() query: GetRankingQuery) {
		return this.statsService.getRanking(query.n);
	}

	@Patch(':nickname')
	@UseGuards(AuthGuard('jwt-acess-token'))
	update(@Param('nickname') nickName: string, @Body() updateStatDto: UpdateStatDto) {
		return this.statsService.update(nickName, updateStatDto);
	}

//   @Delete(':id')
//   remove(@Param('id') id: string) {
//     return this.statsService.remove(+id);
//   }
	
}
