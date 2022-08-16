import { atom } from 'recoil';
import { v1 } from 'uuid';
import { gameType, channelType, inviteType } from 'types/GameTypes';

export const channelState = atom<channelType>({
  key: `channelState/${v1()}`,
  default: {
    channelId: '',
    firstPlayer: '',
    secondPlayer: '',
  },
});

export const countState = atom<string>({
  key: `countState/${v1()}`,
  default: '',
});

export const gameState = atom<gameType>({
  key: `gameState/${v1()}`,
  default: {
    firstPlayerScore: 0,
    secondPlayerScore: 0,
    firstPlayerPaddle: 0,
    secondPlayerPaddle: 0,
    ball: {
      x: 0,
      y: 0,
    },
  },
});

export const inviteState = atom<inviteType>({
  key: `inviteState/${v1()}`,
  default: {
    gameMode: '',
    nickName: '',
    password: '',
    oppNickName: '',
  },
});

export const matchState = atom<boolean>({
  key: `matchState/${v1()}`,
  default: false,
});
