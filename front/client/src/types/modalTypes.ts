type MainModal = 'START';

type UserModal = 'NICK' | 'AVATAR';

type SideModal = 'USER';

type GameModal = 'SETTING' | 'PASSWORD' | 'INVITE' | 'ACCEPT';

type ModalName =
  | null
  | `MAIN-${MainModal}`
  | `USER-${UserModal}`
  | `SIDE-${SideModal}`
  | `GAME-${GameModal}`
  | `GUIDE`
  | `LOGOUT`;

export interface ModalInfo {
  modalName: ModalName;
  user?: string | null;
}
