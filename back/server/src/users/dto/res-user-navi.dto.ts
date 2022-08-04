import { User } from '../entities/user.entity';

export class ResUserNavi {
  nickName: string;
  avatar: string;
  isSecondAuth: boolean;
  constructor(user: User) {
    this.nickName = user.nickname;
    this.avatar = user.avatar;
    this.isSecondAuth = user.is_second_auth;
  }
}
