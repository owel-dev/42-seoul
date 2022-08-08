import { User } from '../entities/user.entity';
import { ApiProperty } from '@nestjs/swagger';

export class ResUserNavi {
  @ApiProperty({ description: '유저 닉네임' })
  nickName: string;

  @ApiProperty({ description: '유저 아바타' })
  avatar: string;

  @ApiProperty({ description: '유저 이차인증 여부' })
  isSecondAuth: boolean;
}
