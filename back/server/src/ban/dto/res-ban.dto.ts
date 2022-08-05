import { ApiProperty } from '@nestjs/swagger';
import { Ban } from '../entities/ban.entity';

export class ResBanDto {
  @ApiProperty({ description: '유저의 닉네임' })
  nickName: string;
}
