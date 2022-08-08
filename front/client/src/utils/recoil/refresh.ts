import { atom } from 'recoil';
import { v1 } from 'uuid';

export const refreshState = atom<boolean>({
  key: `refreshState/${v1()}`,
  default: false,
});
