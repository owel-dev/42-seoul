import { Controller, Get, Post, Body, Patch, Param, Delete, UseGuards } from '@nestjs/common';
import { MatchService } from './match.service';
import { CreateMatchDto } from './dto/create-match.dto';
import { UpdateMatchDto } from './dto/update-match.dto';
import { AuthGuard } from '@nestjs/passport';

@Controller('match')
export class MatchController {
  constructor(private readonly matchService: MatchService) {}

	@UseGuards(AuthGuard('jwt-access-token'))
	@Post()
  	create(@Body() createMatchDto: CreateMatchDto) {
	return this.matchService.create(createMatchDto);
	}

//   @Get()
//   findAll() {
//     return this.matchService.findAll();
//   }

	@UseGuards(AuthGuard('jwt-access-token'))
	@Get(':nickname')
	getMatchListOne(@Param('nickname') nickName: string) {
	return this.matchService.getMatchListOne(nickName);
	}

// //   @Patch(':id')
// //   update(@Param('id') id: string, @Body() updateMatchDto: UpdateMatchDto) {
// //     return this.matchService.update(+id, updateMatchDto);
// //   }

// //   @Delete(':id')
// //   remove(@Param('id') id: string) {
// //     return this.matchService.remove(+id);
// //   }
}
