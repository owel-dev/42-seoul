import { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { useRecoilState } from 'recoil';
import { errorState } from 'utils/recoil/error';
import styles from 'styles/error/error.module.css';

export default function Error() {
  const [errorMessage, setErrorMessage] = useRecoilState(errorState);
  const navigate = useNavigate();

  useEffect(() => {}, []);

  const goHome = () => {
    setErrorMessage('');
    navigate('');
  };

  return (
    <div className={styles.errorContainer}>
      <div className={styles.innerContainer}>
        <div className={styles.title}>{'ERROR'}</div>

        <div className={styles.content}>
          {errorMessage === 'E404'
            ? '잘못된 요청입니다!'
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
