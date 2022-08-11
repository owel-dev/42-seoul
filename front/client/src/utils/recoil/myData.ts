import { atom } from 'recoil';
import { v1 } from 'uuid';
import { myData } from '../../types/myDataTypes';

export const myDataState = atom<myData>({
  key: `myDataState/${v1()}`, // unique ID (다른 atoms/selectors을 구별하기 위해서)
  default: {
    nickName: '',
    avatar: '',
    owner: false,
    admin: false,
    isSecondAuth: false,
    enable2FA: false,
  }, // default value (aka initial value)
});
