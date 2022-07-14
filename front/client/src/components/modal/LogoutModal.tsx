import { useSetRecoilState } from 'recoil';
import { modalState } from 'types/modal';
import 'styles/modal/LogoutModal.css';

function LogoutModal() {
  const setModalInfo = useSetRecoilState(modalState);

  const onReturn = () => {
    setModalInfo({ modalName: null });
  };

  const onLogout = () => {
    setModalInfo({ modalName: null });
  };

  return (
    <div className='container'>
      <div className='title'>Logout</div>
      <div className='content'>
        <div>
          로그아웃
          <br />
          하시겠습니까?
        </div>
      </div>
      <div className='select'>
        <span className='selectButton'>
          <input onClick={onLogout} type='button' value='예' />
        </span>
        <span className='selectButton'>
          <input onClick={onReturn} type='button' value='아니오' />
        </span>
      </div>
    </div>
  );
}

export default LogoutModal;
