import { Stat } from '../entities/stat.entity';

export class ResStatDto {
	nickName: string;
	win: number;
	lose: number;
	winRate: string;

	constructor (stat: Stat) {
		this.nickName = stat.user.nickname;
		this.win = stat.win;
		this.lose = stat.lose;
		this.winRate = (stat.winrate * 100).toFixed() + "%";
	}
}
