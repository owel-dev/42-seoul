import { useState } from 'react';
import { useRecoilState, useRecoilValue } from 'recoil';
import { myData } from 'types/myDataTypes';
import { myDataState } from 'utils/recoil/myData';
import instance from 'utils/axios';
import styles from 'styles/login/login.module.css';
import 'styles/login/SecondAuth.css';

function SecondAuth() {
  const [myData, setMyData] = useRecoilState<myData>(myDataState);
  const [emailInput, setEmailInput] = useState<string>('');
  const [codeInput, setCodeInput] = useState<string>('');

  const sendEmail = async () => {
    try {
      console.log(myData.nickName);
      // await instance.post(`/oauth/sendEmail?id=${myData.nickName}`, {
      await instance.post(`/oauth/sendEmail?id=ulee`, {
        email: emailInput,
      });
    } catch (e) {}
  };
  const submitCode = async () => {
    try {
      console.log(myData.nickName);
      // await instance.post(`/oauth/validEmail?id=${myData.nickName}`, {
      const res = await instance.post(`/oauth/validEmail?id=ulee`, {
        code: codeInput,
      });
      setMyData(res?.data);
    } catch (e) {}
  };

  return (
    <div className={styles.loginContainer}>
      <div className={styles.innerContainer}>
        <div className='submitFrame'>
          <label className='submitLabel'>email</label>
          <input
            className='submitInput'
            onChange={(e) => setEmailInput(e.target.value)}
          />
          <button className='submitButton' onClick={sendEmail}>
            발송
          </button>
        </div>
        <div className='submitFrame'>
          <label className='submitLabel'>코드</label>
          <input
            className='submitInput'
            onChange={(e) => setCodeInput(e.target.value)}
          />
          <button className='submitButton' onClick={submitCode}>
            확인
          </button>
        </div>
      </div>
    </div>
  );
}

export default SecondAuth;
