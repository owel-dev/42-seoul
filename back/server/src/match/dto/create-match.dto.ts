import { Type } from 'class-transformer';
import { IsInt, Min, Max, IsIn } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class CreateMatchDto {
  @ApiProperty({ description: '플레이어 1의 닉네임' })
  player1: string;

  @ApiProperty({ description: '플레이어 2의 닉네임' })
  player2: string;

  @ApiProperty({ description: '플레이어 1의 점수' })
  @Type(() => Number)
  @IsInt()
  @Min(0)
  @Max(10)
  score1: number;

  @ApiProperty({ description: '플레이어 2의 점수' })
  @Type(() => Number)
  @IsInt()
  @Min(0)
  @Max(10)
  score2: number;

  @ApiProperty({ description: '게임 모드' })
  @IsIn(["none", "power", "map"])
  mode: string;
}
