import { atom } from 'recoil';
import { v1 } from 'uuid';

export const friendState = atom<boolean>({
  key: `friendState/${v1()}`,
  default: false,
});
