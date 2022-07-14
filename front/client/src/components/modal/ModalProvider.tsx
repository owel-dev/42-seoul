import { useRecoilState } from 'recoil';
import { modalState } from 'types/modal';
import GameStartModal from './GameStartModal';
import NickChangeModal from './NickChangeModal';
import AvatarChangeModal from './AvatarChangeModal';
import ProfileModal from './ProfileModal';
import LogoutModal from './LogoutModal';
import 'styles/modal/Modal.css';
// import { convertCompilerOptionsFromJson } from 'typescript';

export default function ModalProvider() {
  const [modalInfo, setModalInfo] = useRecoilState(modalState);

  const modalCloseHandler = (e: React.MouseEvent) => {
    if (e.target instanceof HTMLDivElement && e.target.id === 'modalOutside') {
      setModalInfo({ modalName: null });
    }
  };

  const findModal = () => {
    console.log(modalInfo);
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
