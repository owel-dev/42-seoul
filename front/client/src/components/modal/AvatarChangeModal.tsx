import { avatarChangeModalState } from 'utils/recoil/modalState';
import { useRecoilState } from 'recoil';
import 'styles/modal/Modal.css';

function AvatarChangeModal() {
  const [status, setStatus] = useRecoilState(avatarChangeModalState);
  const CloseModal = () => {
    setStatus(false);
  };
  if (status === false) return <div></div>;
  else
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
