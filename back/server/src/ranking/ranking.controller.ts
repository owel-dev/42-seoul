import { Controller, Get, Post, Body, Patch, Param, Delete, Query } from '@nestjs/common';
import { RankingService } from './ranking.service';

@Controller('ranking')
export class RankingController {
  constructor(private readonly rankingService: RankingService) {}

  @Get()
  getRanking(@Query('n') numUser: number) {
	  return this.rankingService.getRanking(numUser);
  }
}
