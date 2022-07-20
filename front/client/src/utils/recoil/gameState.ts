import { atom } from 'recoil';
import { gameType, channelType } from 'types/GameTypes';

export const channelState = atom<channelType>({
  key: 'channelState',
  default: {
    channelId: null,
    firstPlayer: null,
    secondPlayer: null,
  },
});

export const countState = atom<string>({
  key: 'countState',
  default: '',
});

export const gameState = atom<gameType>({
  key: 'gameState',
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
