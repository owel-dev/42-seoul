import { Stat } from 'src/stats/entities/stat.entity';
import { ApiProperty } from '@nestjs/swagger';

export class ResRankDto {
  @ApiProperty({ description: '현재 순위' })
  rank: number;

  @ApiProperty({ description: '유저 닉네임' })
  nickName: string;

  @ApiProperty({ description: '유저 승수' })
  win: number;

  @ApiProperty({ description: '유저 패수' })
  lose: number;

  @ApiProperty({ description: '유저 승률' })
  winRate: string;
}
