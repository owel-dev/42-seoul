import { Ban } from "../entities/ban.entity";

class	ResBan {
	nickName: string;

	constructor (
		_nickName: string,
		) {
		this.nickName = _nickName;
	}
}

export class ResBanListDto {
	banList: ResBan[];

	banToResBanArr(banRepository: Ban[])
	{
		this.banList = banRepository.map(
			(ban, index, array) => {
				return new ResBan(ban.ban_2.nickname);	 
			}
		);
	}
}