import { useEffect, useState } from 'react';
import { useSetRecoilState, useRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import instance from 'utils/axios';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const setModalInfo = useSetRecoilState(modalState);
  const [myData, setMyData] = useRecoilState(myDataState);
  const [inputValue, setInputValue] = useState('');
  const [isChange, setIsChange] = useState<boolean>();

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    getMyData();
    if (isChange) {
      window.location.replace(`/users/${myData.nickName}/mypage`);
      console.log('useEffect', myData);
      setIsChange(false);
    }
  }, [isChange && myData]);

  const getMyData = async () => {
    try {
      const res = await instance.get(`/users/navi`);
      setMyData(res?.data);
      console.log('getData', myData);
    } catch (e) {}
  };

  function PostNickName() {
    const fetchData = async () => {
      try {
        await instance.patch(`/users/` + myData.nickName, {
          nickName: inputValue,
        });
        setIsChange(true);
      } catch (e) {
        alert('이미 존재하는 닉네임입니다!');
      }
    };
    fetchData();
  }

  return (
    <div className='modal'>
      <div className='modal-title'>nickname change</div>
      <div className='modal-content'>
        <div>
          <span>nickname </span>
          <input
            placeholder={'닉네임 입력'}
            onChange={(e) => setInputValue(e.target.value)}
          />
        </div>
      </div>
      <div className='modal-select'>
        <button onClick={PostNickName}>change</button>
        <button onClick={CloseModal}>close</button>
      </div>
    </div>
  );
}

export default NickChangeModal;
