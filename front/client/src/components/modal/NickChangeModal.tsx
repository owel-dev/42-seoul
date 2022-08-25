import { useEffect, useState } from 'react';
import { useSetRecoilState, useRecoilState } from 'recoil';
import { useNavigate } from 'react-router-dom';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { errorState } from 'utils/recoil/error';
import { profileState } from 'utils/recoil/profileData';
import { errorType } from 'types/errorTypes';
import { loginState } from 'utils/recoil/login';
import instance from 'utils/axios';
import refreshToken from 'utils/token';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const [myData, setMyData] = useRecoilState(myDataState);
  const [inputValue, setInputValue] = useState('');
  const [isChange, setIsChange] = useState<boolean>();
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const setModalInfo = useSetRecoilState(modalState);
  const setProfileData = useSetRecoilState(profileState);
  const setErrorMessage = useSetRecoilState(errorState);
  const navigate = useNavigate();

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  const logout = () => {
    socket.emit('logout', () => {
      socket.disconnect();
    });
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    if (isChange) {
      setModalInfo({ modalName: null });
      navigate(`/users/${myData.nickName}/mypage`);
      setIsChange(false);
    }
  }, [isChange && myData]);

  function PostNickName() {
    const regexNickname = /^[a-zA-Z0-9]{1,8}$/;
    const fetchData = async () => {
      try {
        await instance.patch(`/users/` + myData.nickName, {
          nickName: inputValue,
        });
        socket.emit('user-list');
        socket.emit('friend-end');
        setMyData((prev) => ({ ...prev, nickName: inputValue }));
        setProfileData((prev) => ({ ...prev, nickName: inputValue }));
        setIsChange(true);
      } catch (err) {
        const e = err as errorType;
        if (e.message === `Network Error`) {
          setErrorMessage('E500');
        } else if (e.response.data.statusCode === 'NC01')
          alert('이미 존재하는 닉네임입니다!');
        else if (e.response.data.statusCode === 401) {
          refreshToken()
            .then(() => {
              if (isLoggedIn === true) fetchData();
            })
            .catch(() => {
              logout();
            });
        } else setErrorMessage('NM01');
      }
    };
    if (inputValue === '') {
      alert('닉네임을 입력해주세요');
    } else if (regexNickname.test(inputValue) === false) {
      alert('닉네임에는 영문자, 숫자만 사용할 수 있습니다');
    } else {
      fetchData();
    }
  }

  return (
    <div className='modal'>
      <div className='modalTitle'>닉네임 변경</div>
      <div className='modalContent'>
        <div>
          <span>nickname </span>
          <input
            placeholder={'닉네임 입력'}
            onChange={(e) => setInputValue(e.target.value)}
          />
        </div>
      </div>
      <div className='modalSelect'>
        <button onClick={PostNickName} className='modalButton'>
          change
        </button>
        <button onClick={CloseModal} className='modalButton'>
          close
        </button>
      </div>
    </div>
  );
}

export default NickChangeModal;
