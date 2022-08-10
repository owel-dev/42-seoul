import { StreamableFile } from '@nestjs/common';
import { createReadStream } from 'fs';
import { User } from '../entities/user.entity';
import { ApiProperty } from '@nestjs/swagger';

export class ResUserMyPage {
  @ApiProperty({ description: '해당 유저 인트라 아이디' })
  intraId: string;

  @ApiProperty({ description: '해당 유저 아바타' })
  avatar: string;

  @ApiProperty({ description: '해당 유저 닉네임' })
  nickName: string;

  @ApiProperty({ description: '해당 유저 승수' })
  win: number;

  @ApiProperty({ description: '해당 유저 패수' })
  lose: number;

  @ApiProperty({ description: '해당 유저 승률' })
  winRate: string;

  @ApiProperty({ description: '해당 유저 친구 여부' })
  isFriend: boolean;
}
