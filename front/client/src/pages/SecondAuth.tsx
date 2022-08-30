import { useState } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { myDataState } from 'utils/recoil/myData';
import { errorState } from 'utils/recoil/error';
import { loginState } from 'utils/recoil/login';
import { errorType } from 'types/errorTypes';
import styles from 'styles/login/login.module.css';
import refreshToken from 'utils/token';
import instance from 'utils/axios';
import 'styles/login/SecondAuth.css';

function SecondAuth() {
  const setErrorMessage = useSetRecoilState(errorState);
  const [myData, setMyData] = useRecoilState(myDataState);
  const [emailInput, setEmailInput] = useState<string>('');
  const [codeInput, setCodeInput] = useState<string>('');
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);

  const logout = () => {
    socket.emit('logout', () => {
      socket.disconnect();
    });
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
  };

  const sendEmail = async () => {
      try {
        await instance.post(`/oauth/sendEmail?id=${myData.nickName}`);
        alert('인트라에 등록된 이메일로 코드가 전송되었습니다');
      } catch (err) {
        const e = err as errorType;
        if (e.message === `Network Error`) {
          setErrorMessage('E500');
        } else if (e.response.data.statusCode === 401) {
          refreshToken()
            .then(() => {
              if (isLoggedIn === true) sendEmail();
            })
            .catch(() => {
              logout();
            });
        } else setErrorMessage('SA01');
      }
  };

  const submitCode = async () => {
    try {
      const res = await instance.post(
        `/oauth/validEmail?id=${myData.nickName}`,
        {
          code: codeInput,
        }
      );
      setMyData(res?.data);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'SC01')
        alert('잘못된 코드입니다.');
      else if (e.response.data.statusCode === 401) {
        refreshToken()
          .then(() => {
            if (isLoggedIn === true) submitCode();
          })
          .catch(() => {
            logout();
          });
      } else setErrorMessage('SA02');
    }
  };

  return (
    <div className={styles.loginContainer}>
      <div className='secondAuthTitle'>2차 인증을 완료해주세요.</div>
      <div className={styles.innerContainer}>
        <label className='secondAuthInfo'>발송 버튼을 누르면 인트라에 등록된 이메일로 인증코드가 발송됩니다</label>
        <div className='submitFrame'>
          <label className='submitLabel'>코드</label>
          <input
            className='submitInput'
            onChange={(e) => setCodeInput(e.target.value)}
          />
          <button className='submitButton' onClick={sendEmail}>
            발송
          </button>
          <button className='submitButton' onClick={submitCode}>
            확인
          </button>
        </div>
      </div>
    </div>
  );
}

export default SecondAuth;
