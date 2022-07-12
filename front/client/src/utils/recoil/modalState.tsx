import { atom } from 'recoil';
import { userInfo } from 'types/MyPageTypes';

export const modalState = atom<boolean>({
  key: 'modalState',
  default: false,
});

export const userState = atom<userInfo>({
  key: 'userState',
  default: {
    user: {
      intraId: '',
      avatar: '',
      nickName: '',
      win: 0,
      lose: 0,
      winRate: '0%',
    },
  },
});
