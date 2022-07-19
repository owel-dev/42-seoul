import { atom } from 'recoil';

export const channelIdState = atom<string | undefined>({
  key: 'channelIdState',
  default: 'lobby',
});
