import { StreamableFile } from "@nestjs/common";
import { createReadStream } from "fs";
import { User } from "../entities/user.entity";

export class ResUserMyPage {
	intraId: string;
	avatar: string;
	nickName: string;
	win: number;
	lose: number;
	winRate: string;

	constructor (user: User) {
		this.intraId = user.intra_id;
		const file = createReadStream(user.avatar)
		this.avatar = user.avatar;
		this.nickName = user.nickname;
		this.win = user.stats.win;
		this.lose = user.stats.lose;
		this.winRate = (user.stats.winrate * 100).toFixed() + "%";
	}
}
