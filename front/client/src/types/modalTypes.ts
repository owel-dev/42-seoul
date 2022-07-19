type MainModal = 'START';

type UserModal = 'NICK' | 'AVATAR';

type SideModal = 'USER';

type GameModal = 'SETTING';

type ModalName =
  | null
  | `MAIN-${MainModal}`
  | `USER-${UserModal}`
  | `SIDE-${SideModal}`
  | `GAME-${GameModal}`
  | `LOGOUT`;

export interface ModalInfo {
  modalName: ModalName;
  user?: string | null;
}
