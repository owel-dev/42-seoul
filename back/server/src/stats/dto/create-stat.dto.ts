import { Type } from "class-transformer";
import { IsInt, Max, Min } from "class-validator";
import { Stat } from "../entities/stat.entity";
import { ApiProperty } from '@nestjs/swagger';

export class CreateStatDto {
	@ApiProperty({ description: ' ' })
	intraId: string;

	@Type(() => Number)
	@IsInt()
	@Min(0)
	win: number;

	@Type(() => Number)
	@IsInt()
	@Min(0)
	lose: number;
}
