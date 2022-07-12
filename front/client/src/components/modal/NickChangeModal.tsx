import { nickChangeModalState } from 'utils/recoil/modalState';
import { useRecoilState } from 'recoil';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const [status, setStatus] = useRecoilState(nickChangeModalState);
  const CloseModal = () => {
    setStatus(false);
  };
  if (status === false) return <div></div>;
  else
    return (
      <div className='modal'>
        <div className='modal-title'>nickname change</div>
        <div className='modal-content'>
          <div>
            <span>nickname </span>
            <input placeholder={'닉네임 입력'}></input>
          </div>
        </div>
        <div className='modal-select'>
          <button>change</button>
          <button onClick={CloseModal}>close</button>
        </div>
      </div>
    );
}

export default NickChangeModal;
