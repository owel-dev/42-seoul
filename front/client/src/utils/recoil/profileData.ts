import { atom } from 'recoil';
import { v1 } from 'uuid';
import { profileType } from '../../types/profileTypes';

export const profileState = atom<profileType>({
  key: `profileState/${v1()}`, // unique ID (다른 atoms/selectors을 구별하기 위해서)
  default: {
    intraId: '',
    avatar: '',
    nickName: '',
    win: 0,
    lose: 0,
    winRate: '',
    isFriend: false,
  }, // default value (aka initial value)
});
