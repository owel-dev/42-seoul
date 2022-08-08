import { match } from 'assert';
import { Match } from '../entities/match.entity';
import { ApiProperty } from '@nestjs/swagger';

export class ResMatchDto {
  @ApiProperty({ description: '플레이어 1의 닉네임' })
  player1: string;

  @ApiProperty({ description: '플레이어 2의 닉네임' })
  player2: string;

  @ApiProperty({ description: '플레이어 1의 점수' })
  score1: number;

  @ApiProperty({ description: '플레이어 2의 점수' })
  score2: number;

  @ApiProperty({ description: '게임 모드' })
  mode: string;
}
