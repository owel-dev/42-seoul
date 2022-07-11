import { match } from "assert";
import { Match } from "../entities/match.entity";

class	ResMatch {
	player1: string;
	player2: string;
	score1: number;
	score2: number;
	mode: string;

	constructor (
		_player1: string,
		_player2: string,
		_score1: number,
		_score2: number,
		_mode: string) {
		this.player1 = _player1;
		this.player2 = _player2;
		this.score1 = _score1;
		this.score2 = _score2;
		this.mode = _mode;
	}
}

export class ResMatchDto {
	matchList: ResMatch[];

	set matchArr(matchRepository: Match[]) {
		this.matchList = this.matchToResMatchArr(matchRepository);
	}

	private matchToResMatchArr(matchRepository: Match[]) : ResMatch[]
	{
		return matchRepository.map(
			(match, index, array) => {
				return new ResMatch(match.player_1.nickname, match.player_2.nickname, match.score_1, match.score_2, match.mode);
			}
		);
	}
}