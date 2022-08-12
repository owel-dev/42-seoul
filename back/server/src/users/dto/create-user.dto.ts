import { IsAlphanumeric, IsEmail, Length } from 'class-validator';
import { ApiProperty } from '@nestjs/swagger';

export class CreateUserDto {
  @ApiProperty({ description: '유저 인트라 아이디' })
  @Length(1, 8)
  intraId: string;

  @ApiProperty({ description: '유저 닉네임' })
  @Length(1, 8)
  @IsAlphanumeric()
  nickName: string;

  @ApiProperty({ description: '유저 인트라 이메일' })
  @IsEmail()
  intraEmail: string;

  @ApiProperty({ description: '유저 아바타' })
  avatar: string;

  @ApiProperty({ description: '유저 현재 상태' })
  status?: string;

  @ApiProperty({ description: '유저 현재 채널' })
  channelId?: string;

  @ApiProperty({ description: '유저 access token' })
  access_token: string;

  @ApiProperty({ description: '유저 이차 인증 활성화 여부' })
  enable2FA?: boolean;
}
