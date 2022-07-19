import { Type } from "class-transformer";
import { IsInt, Min, Max, IsIn } from "class-validator"

export class CreateMatchDto {
	player1: string;
	player2: string;

	@Type(() => Number)
	@IsInt()
	@Min(0)
	@Max(10)
	score1: number;

	@Type(() => Number)
	@IsInt()
	@Min(0)
	@Max(10)
	score2: number;

	@IsIn(["default", "power", "obstacle"])
	mode: string;
}
