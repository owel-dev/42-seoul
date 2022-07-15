import { Controller, Get, Post, Body, Patch, Param, Delete, Query } from '@nestjs/common';
import { StatsService } from './stats.service';
import { CreateStatDto } from './dto/create-stat.dto';
import { UpdateStatDto } from './dto/update-stat.dto';
import { IsInt, IsNumber, IsOptional, Min } from 'class-validator';
import { Type } from 'class-transformer';

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
	getRanking(@Query() query: GetRankingQuery) {
		return this.statsService.getRanking(query.n);
	}

	@Patch(':intraid')
	update(@Param('intraid') id: string, @Body() updateStatDto: UpdateStatDto) {
		return this.statsService.update(id, updateStatDto);
	}

//   @Delete(':id')
//   remove(@Param('id') id: string) {
//     return this.statsService.remove(+id);
//   }
	
}
