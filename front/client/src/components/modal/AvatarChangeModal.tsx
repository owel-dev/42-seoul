import { useSetRecoilState } from 'recoil';
import { modalState } from 'types/modal';
import 'styles/modal/Modal.css';

function AvatarChangeModal() {
  const setModalInfo = useSetRecoilState(modalState);

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  return (
    <div className='modal'>
      <div className='modal-title'>avatar change</div>
      <div className='modal-content'>
        <div>
          <span>아바타</span>
        </div>
      </div>
      <div className='modal-select'>
        <button>change</button>
        <button onClick={CloseModal}>close</button>
      </div>
    </div>
  );
}

export default AvatarChangeModal;
