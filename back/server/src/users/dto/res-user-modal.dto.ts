import { ChatService } from 'src/chat/chat.service';
import { User } from '../entities/user.entity';
import { ApiProperty } from '@nestjs/swagger';

export class ResUserModal {
  @ApiProperty({ description: '해당 유저 닉네임' })
  nickName: string;

  @ApiProperty({ description: '해당 유저 승수' })
  win: number;

  @ApiProperty({ description: '해당 유저 패수' })
  lose: number;

  @ApiProperty({ description: '해당 유저 승률' })
  winRate: string;

  @ApiProperty({ description: '해당 유저 현재 상태' })
  status: string;

  @ApiProperty({ description: '해당 유저 현재 채널' })
  channelId: string;

  @ApiProperty({ description: '해당 유저 친구 여부' })
  friend: boolean;

  @ApiProperty({ description: '해당 유저 차단 여부' })
  ban: boolean;

  @ApiProperty({ description: '해당 유저 채널 소유자 여부' })
  owner: boolean;

  @ApiProperty({ description: '요청 유저 채널 관리자 여부' })
  admin: boolean;
}
