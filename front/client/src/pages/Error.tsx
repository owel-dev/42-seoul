import { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { errorState } from 'utils/recoil/error';
import { loginState } from 'utils/recoil/login';
import styles from 'styles/error/error.module.css';

export default function Error() {
  const [errorMessage, setErrorMessage] = useRecoilState(errorState);
  const setModalInfo = useSetRecoilState(modalState);
  const setIsLoggedIn = useSetRecoilState(loginState);
  const navigate = useNavigate();

  const goHome = () => {
    if (errorMessage === 'E500') {
      localStorage.removeItem('trans-token');
      setIsLoggedIn(false);
    }
    setErrorMessage('');
    setModalInfo({ modalName: null });
    navigate('');
  };

  return (
    <div className={styles.errorContainer}>
      <div className={styles.innerContainer}>
        <div className={styles.title}>{'ERROR'}</div>

        <div className={styles.content}>
          {errorMessage === 'E404'
            ? '잘못된 요청입니다!'
            : errorMessage === 'E500'
            ? '네트워크 오류가 발생하였습니다.'
            : '데이터 요청에 실패하였습니다.'}
        </div>
        <div className={styles.message}>({errorMessage})</div>
        <div onClick={goHome}>
          <input
            type='button'
            className={styles.buttons}
            value='🏠 홈으로 🏠'
          />
        </div>
      </div>
    </div>
  );
}
