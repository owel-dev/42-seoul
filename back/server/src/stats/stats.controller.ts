import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  Query,
  UseGuards,
} from '@nestjs/common';
import { StatsService } from './stats.service';
import { UpdateStatDto } from './dto/update-stat.dto';
import { IsInt, IsNumber, IsOptional, Min } from 'class-validator';
import { Type } from 'class-transformer';
import { AuthGuard } from '@nestjs/passport';
import { ApiTags, ApiOperation } from '@nestjs/swagger';

class GetRankingQuery {
  @IsOptional()
  @Type(() => Number)
  @IsInt()
  @Min(1)
  n: number;
}

@Controller('stat')
@ApiTags('친구 관련 API')
export class StatsController {
  constructor(private readonly statsService: StatsService) {}

  @Get()
  @ApiOperation({
    summary: '랭킹리스트 api',
    description: '현재 랭킹리스트를 가져옵니다.',
  })
  //   @UseGuards(AuthGuard('jwt-access-token'))
  getRanking(@Query() query: GetRankingQuery) {
    return this.statsService.getRanking(query.n);
  }

  //   @Patch(':nickname')
  //   @ApiOperation({ summary: ' ', description: ' ' })
  //   @UseGuards(AuthGuard('jwt-access-token'))
  //   update(
  //     @Param('nickname') nickName: string,
  //     @Body() updateStatDto: UpdateStatDto,
  //   ) {
  //     return this.statsService.update(nickName, updateStatDto);
  //   }

  //   @Delete(':id')
  //   remove(@Param('id') id: string) {
  //     return this.statsService.remove(+id);
  //   }
}
