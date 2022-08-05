import {
  Controller,
  Get,
  Post,
  Body,
  Param,
  Delete,
  Query,
  HttpCode,
  UseGuards,
} from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';
import { BanService } from './ban.service';
import { CreateBanDto } from './dto/create-ban.dto';
import { UpdateBanDto } from './dto/update-ban.dto';
import { ApiTags, ApiOperation } from '@nestjs/swagger';

@Controller('ban')
@ApiTags('Ban(차단) API')
export class BanController {
  constructor(private readonly banService: BanService) {}

  @Post()
  @ApiOperation({ summary: '유저 차단 API', description: '유저를 차단합니다.' })
  @UseGuards(AuthGuard('jwt-access-token'))
  create(@Body() createBanDto: CreateBanDto) {
    return this.banService.create(createBanDto);
  }

  @Get(':nickname')
  @ApiOperation({
    summary: '차단 리스트 API',
    description: '유저의 차단 목록을 가져옵니다.',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  findOne(@Param('nickname') nickName: string) {
    return this.banService.getBanListOne(nickName);
  }

  @Delete()
  @ApiOperation({
    summary: '차단 해제 API',
    description: '유저의 차단을 해제합니다.',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  @HttpCode(204)
  deleteBan(@Query('player1') player1: string, @Query('player2') player2) {
    return this.banService.deleteBan(player1, player2);
  }
}
