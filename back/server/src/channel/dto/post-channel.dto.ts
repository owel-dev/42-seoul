import { ApiProperty } from '@nestjs/swagger';

export class PostChannelDto {
    @ApiProperty({ description: ' ' })
    player1: string;

    @ApiProperty({ description: ' ' })
    player2: string;

    @ApiProperty({ description: ' ' })
    admin: string;

    @ApiProperty({ description: ' ' })
    curNumUser: number;

    @ApiProperty({ description: ' ' })
    maxNumUser: number

    @ApiProperty({ description: ' ' })
    password: string


    @ApiProperty({ description: ' ' })
    mode: number


    @ApiProperty({ description: ' ' })
    type: number

}
