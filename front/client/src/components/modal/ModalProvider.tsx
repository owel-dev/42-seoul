import { useRecoilState, useRecoilValue } from 'recoil';
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
import GameGuideModal from './GameGuideModal';
import { inviteState, matchState } from 'utils/recoil/gameState';
import { inviteType } from 'types/GameTypes';
import 'styles/modal/Modal.css';

export default function ModalProvider() {
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const [matchWait, setMatchWait] = useRecoilState(matchState);
  const inviteData = useRecoilValue<inviteType>(inviteState);

  const modalCloseHandler = (e: React.MouseEvent) => {
    if (e.target instanceof HTMLDivElement && e.target.id === 'modalOutside') {
      if (
        modalInfo.modalName === 'MAIN-START' ||
        modalInfo.modalName === 'GAME-INVITE'
      ) {
        socket.emit('match-cancel', modalInfo.user);
        setMatchWait(false);
      }
      if (modalInfo.modalName === 'GAME-ACCEPT') {
        socket.emit('together-response', { status: false, data: inviteData });
      }
      setModalInfo({ modalName: null });
    }
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
      case 'GUIDE':
        return <GameGuideModal />;
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
