import { Friend } from "../entities/friend.entity";

class	ResFriend {
	nickName: string;
	status: string;

	constructor (
		_nickName: string,
		_status: string,
		) {
		this.nickName = _nickName;
		this.status = _status;
	}
}

export class ResFriendListDto {
	friendList: ResFriend[];

	friendToResFriendArr(friendRepository: Friend[], intraId: string)
	{
		this.friendList = friendRepository.map(
			(friend, index, array) => {
				if (friend.friend_1.intra_id === intraId)
					return new ResFriend(friend.friend_2.nickname, friend.friend_2.status);
				else (friend.friend_2.intra_id === intraId)
					return new ResFriend(friend.friend_1.nickname, friend.friend_1.status);		 
			}
		);
	}
}