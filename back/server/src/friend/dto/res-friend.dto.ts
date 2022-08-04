import { Friend } from '../entities/friend.entity';

export class ResFriend {
  nickName: string;
  status: string;

  constructor(_nickName: string, _status: string) {
    this.nickName = _nickName;
    this.status = _status;
  }
}

export class ResFriendListDto {
  friendList: ResFriend[];

  friendToResFriendArr(friendRepository: Friend[]) {
    this.friendList = friendRepository.map((friend, index, array) => {
      return new ResFriend(friend.friend_2.nickname, friend.friend_2.status);
    });
  }
}
