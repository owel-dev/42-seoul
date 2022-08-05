import { ApiProperty } from '@nestjs/swagger';

export class CreateBanDto {
  // 요청 보낸사람
  @ApiProperty({ description: '유저 차단을 한 유저의 닉네임' })
  player1: string;
  // 요청 받은사람
  @ApiProperty({ description: '유저 차단을 받은 유저의 닉네임' })
  player2: string;
}
