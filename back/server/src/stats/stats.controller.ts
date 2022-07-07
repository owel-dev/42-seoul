import { Controller, Get, Post, Body, Patch, Param, Delete, Query } from '@nestjs/common';
import { StatsService } from './stats.service';
import { CreateStatDto } from './dto/create-stat.dto';
import { UpdateStatDto } from './dto/update-stat.dto';
import internal from 'stream';

@Controller('stats')
export class StatsController {
  constructor(private readonly statsService: StatsService) {}

  @Post()
  create(@Body() createStatDto: CreateStatDto) {
    return this.statsService.create(createStatDto);
  }

//   @Get()
//   findAll() {
//     return this.statsService.findAll();
//   }

	@Get(':intraId')
	findOne(@Param('intraId') intraId: string) {
		// const stat = this.statsService.findOne(intraId);
		return this.statsService.findOne(intraId);
	}

//   @Patch(':id')
//   update(@Param('id') id: string, @Body() updateStatDto: UpdateStatDto) {
//     return this.statsService.update(+id, updateStatDto);
//   }

//   @Delete(':id')
//   remove(@Param('id') id: string) {
//     return this.statsService.remove(+id);
//   }
}
