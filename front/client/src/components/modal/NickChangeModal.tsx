import axios from 'axios';
import { useEffect, useState } from 'react';
import { useSetRecoilState } from 'recoil';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import { modalState } from 'types/modal';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const setModalInfo = useSetRecoilState(modalState);
  const [inputValue, setInputValue] = useState('');
  const [isChange, setIsChange] = useState<boolean>();

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    if (isChange) {
      window.location.reload();
      setIsChange(false);
    }
  }, [isChange]);

  function PostNickName() {
    const fetchData = async () => {
      try {
        await axios.patch(
          DUMMY_SERVER + '/users/' + DUMMY_USER.intraId,
          { nickName: inputValue },
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
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
