import { useRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { socket } from 'components/layout/Layout';
import GameStartModal from './GameStartModal';
import NickChangeModal from './NickChangeModal';
import AvatarChangeModal from './AvatarChangeModal';
import ProfileModal from './ProfileModal';
import LogoutModal from './LogoutModal';
import ChannelSettingModal from './ChannelSettingModal';
import PasswordSubmitModal from './PasswordSubmitModal';
import GameInviteModal from './GameInviteModal';
import InviteAcceptModal from './InviteAcceptModal';
import 'styles/modal/Modal.css';

export default function ModalProvider() {
  const [modalInfo, setModalInfo] = useRecoilState(modalState);

  const modalCloseHandler = (e: React.MouseEvent) => {
    if (e.target instanceof HTMLDivElement && e.target.id === 'modalOutside') {
      setModalInfo({ modalName: null });
    }
    if (modalInfo.modalName === 'MAIN-START') socket.emit('match-cancel');
  };

  const findModal = () => {
    const { modalName } = modalInfo;
    switch (modalName) {
      case 'MAIN-START':
        return <GameStartModal />;
      case 'USER-NICK':
        return <NickChangeModal />;
      case 'USER-AVATAR':
        return <AvatarChangeModal />;
      case 'SIDE-USER':
        return <ProfileModal />;
      case 'LOGOUT':
        return <LogoutModal />;
      case 'GAME-SETTING':
        return <ChannelSettingModal />;
      case 'GAME-PASSWORD':
        return <PasswordSubmitModal />;
      case 'GAME-INVITE':
        return <GameInviteModal />;
      case 'GAME-ACCEPT':
        return <InviteAcceptModal />;
      default:
        return null;
    }
  };

  return (
    modalInfo.modalName && (
      <div className='backdrop' id='modalOutside' onClick={modalCloseHandler}>
        <div className='modalContainer'>{findModal()}</div>
      </div>
    )
  );
}
