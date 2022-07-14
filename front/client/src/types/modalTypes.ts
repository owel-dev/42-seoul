type MainModal = 'START';

type UserModal = 'NICK' | 'AVATAR';

type SideModal = 'USER';

type ModalName =
  | null
  | `MAIN-${MainModal}`
  | `USER-${UserModal}`
  | `SIDE-${SideModal}`
  | `LOGOUT`;

export interface ModalInfo {
  modalName: ModalName;
  user?: string;
}
