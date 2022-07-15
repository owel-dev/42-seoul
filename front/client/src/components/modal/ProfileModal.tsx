import { useRecoilState } from 'recoil';
import { modalState } from 'types/modal';
import 'styles/modal/Modal.css';

function ProfileModal() {
  const [modalInfo, setModalInfo] = useRecoilState(modalState);

  const ProfileModalClose = () => {
    setModalInfo({ modalName: null, user: null });
  };

  return (
    <div className='modal'>
      <div className='modal-title'>유저 프로필</div>
      <div className='modal-content'>
        <section>
          <span>{modalInfo.user}</span>
          <button>프로필</button>
          <br />
          <span>n 승 </span>
          <span>n 패 </span>
          <span>승률 n%</span>
        </section>
        <section>
          <button>같이하기</button>
          <button>관전하기</button>
          <button>친구추가</button>
          <button>차단하기</button>
        </section>
      </div>
      <div className='modal-select'>
        <button onClick={ProfileModalClose}>닫기</button>
      </div>
    </div>
  );
}
export default ProfileModal;
