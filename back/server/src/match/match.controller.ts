import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  UseGuards,
} from '@nestjs/common';
import { MatchService } from './match.service';
import { CreateMatchDto } from './dto/create-match.dto';
import { UpdateMatchDto } from './dto/update-match.dto';
import { AuthGuard } from '@nestjs/passport';
import { ApiTags, ApiOperation, ApiResponse } from '@nestjs/swagger';

@Controller('match')
@ApiTags('친구 관련 API')
export class MatchController {
  constructor(private readonly matchService: MatchService) {}

  @Post()
  @ApiOperation({
    summary: '경기 기록 저장 API',
    description: '경기 기록을 저장합니다.',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  create(@Body() createMatchDto: CreateMatchDto) {
    return this.matchService.create(createMatchDto);
  }

  //   @Get()
  //   findAll() {
  //     return this.matchService.findAll();
  //   }

  @Get(':nickname')
  @ApiOperation({
    summary: '경기 기록 조회 API',
    description: '유저의 경기 기록을 가져옵니다',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
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
