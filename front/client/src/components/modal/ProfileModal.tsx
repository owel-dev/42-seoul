import { useRecoilState, useSetRecoilState } from 'recoil';
import { profileModalState } from 'utils/recoil/modalState';
import { modalState } from 'types/modal';
import 'styles/modal/Modal.css';

function ProfileModal() {
  //profileModalStat에 해당 유저 닉네임이 저장되어 있으니 /stat/{status}로 get요청 하기
  const [status, setStatus] = useRecoilState(profileModalState);
  const setModalInfo = useSetRecoilState(modalState);

  const ProfileModalClose = () => {
    setStatus(null);
    setModalInfo({ modalName: null });
  };

  return (
    <>
      {status && (
        <div className='modal'>
          <div className='modal-title'>유저 프로필</div>
          <div className='modal-content'>
            <section>
              <span>{status}</span>
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
      )}
    </>
  );
}
export default ProfileModal;
