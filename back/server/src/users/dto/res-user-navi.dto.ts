import { User } from "../entities/user.entity";

export class ResUserNavi {
	nickName: string;
	avatar: string;
	admin: boolean;
	constructor (user: User) {
		this.nickName = user.nickname;
		this.avatar = user.avatar;
		this.admin = true;
	}
}