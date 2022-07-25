import { atom } from 'recoil';
import { v1 } from 'uuid';

export const chatScrollState = atom<boolean>({
  key: `chatScrollState/${v1()}`,
  default: false,
});
