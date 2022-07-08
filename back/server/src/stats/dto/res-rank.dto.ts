import { Stat } from "src/stats/entities/stat.entity";

class	UserRank {
	rank: number;
	nickName: string;
	win: number;
	lose: number;
	winRate: string;

	constructor (
		_rank: number,
		_nickName: string,
		_win: number,
		_lose: number,
		_winRate: number) {
		this.rank = _rank;
		this.nickName = _nickName;
		this.win = _win;
		this.lose = _lose;
		this.winRate = (_winRate * 100).toFixed() + "%";
	}
}

export class ResRankDto {
	ranking: UserRank[];

	set rankingArr(statRepository: Stat[]) {
		this.ranking = this.statToRankArr(statRepository);
	}

	private statToRankArr(statRepository: Stat[]) : UserRank[]
	{
		return statRepository.map(
			(stat, index, array) => {
				const rank = array.filter((iter) =>
				(iter.win > stat.win) ||
				((iter.win === stat.win) && iter.winrate > stat.winrate)).length + 1;
				return new UserRank(rank, stat.user.nickname, stat.win, stat.lose, stat.winrate);
			}
		);
	}
}
