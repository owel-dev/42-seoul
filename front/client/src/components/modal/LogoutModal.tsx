import { useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { loginState } from 'utils/recoil/login';
import 'styles/modal/LogoutModal.css';

function LogoutModal() {
  const setModalInfo = useSetRecoilState(modalState);
  const setIsLoggedIn = useSetRecoilState(loginState);

  const onReturn = () => {
    setModalInfo({ modalName: null });
  };

  const onLogout = () => {
    socket.disconnect();
    localStorage.removeItem('trans-token');
    setIsLoggedIn(false);
    setModalInfo({ modalName: null });
  };

  return (
    <div className='modal'>
      <div className='modalTitle'>Logout</div>
      <div className='modalContent'>
        <div>
          로그아웃
          <br />
          하시겠습니까?
        </div>
      </div>
      <div className='modalSelect'>
        <span>
          <input
            onClick={onLogout}
            type='button'
            value='예'
            className='modalButton'
          />
        </span>
        <span>
          <input
            onClick={onReturn}
            type='button'
            value='아니오'
            className='modalButton'
          />
        </span>
      </div>
    </div>
  );
}

export default LogoutModal;
