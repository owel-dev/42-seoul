import { ApiProperty } from '@nestjs/swagger';

export class GetChannelDto {
    @ApiProperty({ description: ' ' })
    channelId: string;

    @ApiProperty({ description: ' ' })
    player1: string;

    @ApiProperty({ description: ' ' })
    player2: string;

    @ApiProperty({ description: ' ' })
    curNumUser: number;

    @ApiProperty({ description: ' ' })
    maxUser: number;

    @ApiProperty({ description: ' ' })
    password: string;

    @ApiProperty({ description: ' ' })
    type: number;

    @ApiProperty({ description: ' ' })
    gameMode: string;
}