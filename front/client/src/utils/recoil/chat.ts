import { atom } from 'recoil';
import { v1 } from 'uuid';
import { chat } from 'types/chatTypes';

export const chatScrollState = atom<boolean>({
  key: `chatScrollState/${v1()}`,
  default: false,
});

export const messageState = atom<string>({
  key: `messageState/${v1()}`,
  default: '',
});

export const chatListState = atom<chat[]>({
  key: `chatListState/${v1()}`,
  default: [],
});
