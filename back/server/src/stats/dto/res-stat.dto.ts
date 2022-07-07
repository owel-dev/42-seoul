import { Stat } from '../entities/stat.entity';

export class ResStatDto {
	nickName: string;
	win: number;
	lose: number;
	winRate: string;

	constructor (stat: Stat) {
		this.nickName = stat.intra_id; // user_tb와 연결 후 nickName으로 변경 예정
		this.win = stat.win;
		this.lose = stat.lose;
		this.winRate = (stat.winrate * 100).toFixed() + "%";
	}
}
