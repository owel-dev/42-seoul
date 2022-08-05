import { ApiProperty } from '@nestjs/swagger';

export class CreateFriendDto {
  // 요청 보낸사람
  @ApiProperty({ description: '친구 추가를 하는 유저 닉네임' })
  player1: string;
  // 요청 받은사람
  @ApiProperty({ description: '친구 추가를 당한 유저 닉네임' })
  player2: string;
}
