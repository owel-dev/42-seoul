import { User } from '../entities/user.entity';
import { ApiProperty } from '@nestjs/swagger';

export class ResUserNavi {
  @ApiProperty({ description: '유저 닉네임' })
  nickName: string;

  @ApiProperty({ description: '유저 아바타' })
  avatar: string;

  @ApiProperty({ description: '유저 이차인증 여부' })
  isSecondAuth: boolean;

  @ApiProperty({ description: '유저 방 owner 여부' })
  owner: boolean;

  @ApiProperty({ description: '유저 방 admin 여부' })
  admin: boolean;

  @ApiProperty({ description: '유저 이차인증 활성화 여부' })
  enable2FA: boolean;
}
