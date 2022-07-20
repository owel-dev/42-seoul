import { User } from "../entities/user.entity";

export class ResUserModal {
	nickName: string;
	win: number;
	lose: number;
	winRate: string;
	status: string;
	channelId : string;
	friend : boolean;
	ban: boolean

	constructor (user: User) {
		this.nickName = user.nickname;
		this.win = user.stats.win;
		this.lose = user.stats.lose;
		this.winRate = (user.stats.winrate * 100).toFixed() + "%";
		this.status = user.status;
		this.channelId = user.channel_id;
	}

	set setFriend(friend : boolean)
	{
		this.friend = friend;
	}

	set setBan(ban : boolean)
	{
		this.ban = ban;
	}
}
