import { atom } from 'recoil';
import { userInfo } from 'types/MyPageTypes';

export const nickChangeModalState = atom<boolean>({
  key: 'nickChangeModalState',
  default: false,
});

export const avatarChangeModalState = atom<boolean>({
  key: 'avatarChangeModalState',
  default: false,
});

export const gameStartModalState = atom<boolean>({
  key: 'gameStartModalState',
  default: false,
});

export const userState = atom<userInfo>({
  key: 'userState',
  default: {
    intraId: '',
    avatar: '',
    nickName: '',
    win: 0,
    lose: 0,
    winRate: '0%',
  },
});
