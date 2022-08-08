import { useEffect, useState } from 'react';
import { useSetRecoilState, useRecoilState } from 'recoil';
import { useNavigate } from 'react-router-dom';
import instance from 'utils/axios';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { errorState } from 'utils/recoil/error';
import { profileState } from 'utils/recoil/profileData';
import { errorType } from 'types/errorTypes';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const [myData, setMyData] = useRecoilState(myDataState);
  const setModalInfo = useSetRecoilState(modalState);
  const setProfileData = useSetRecoilState(profileState);
  const setErrorMessage = useSetRecoilState(errorState);
  const [inputValue, setInputValue] = useState('');
  const [isChange, setIsChange] = useState<boolean>();
  const navigate = useNavigate();

  const CloseModal = () => {
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
    const regexNickname = /^[a-zA-Z0-9]+$/;
    const fetchData = async () => {
      try {
        await instance.patch(`/users/` + myData.nickName, {
          nickName: inputValue,
        });
        setMyData((prev) => ({ ...prev, nickName: inputValue }));
        setProfileData((prev) => ({ ...prev, nickName: inputValue }));
        setIsChange(true);
      } catch (err) {
        const e = err as errorType;
        if (e.message === `Network Error`) {
          setErrorMessage('E500');
        } else if (e.response.data.statusCode === 'NC01')
          alert('이미 존재하는 닉네임입니다!');
        else setErrorMessage('NM01');
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
      <div className='modalTitle'>nickname change</div>
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
