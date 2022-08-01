import { useEffect, useState } from 'react';
import { useSetRecoilState, useRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { errorState } from 'utils/recoil/error';
import instance from 'utils/axios';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const setModalInfo = useSetRecoilState(modalState);
  const [myData, setMyData] = useRecoilState(myDataState);
  const [inputValue, setInputValue] = useState('');
  const [isChange, setIsChange] = useState<boolean>();
  const setErrorMessage = useSetRecoilState(errorState);

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    if (isChange) {
      window.location.replace(`/users/${myData.nickName}/mypage`);
      setIsChange(false);
    }
  }, [isChange && myData]);

  function PostNickName() {
    const fetchData = async () => {
      try {
        await instance.patch(`/users/` + myData.nickName, {
          nickName: inputValue,
        });
        setIsChange(true);
      } catch (e: any) {
        if (e.response.data.statusCode === 'NC01')
          alert('이미 존재하는 닉네임입니다!');
        else setErrorMessage('NM01');
      }
    };
    fetchData();
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
