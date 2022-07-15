import axios from 'axios';
import { useState } from 'react';
import { useSetRecoilState } from 'recoil';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import { modalState } from 'types/modal';
import 'styles/modal/Modal.css';

function NickChangeModal() {
  const setModalInfo = useSetRecoilState(modalState);

  const [inputValue, setInputValue] = useState('');
  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  function PostNickName() {
    const fetchData = async () => {
      try {
        await axios.patch(
          DUMMY_SERVER + 'users/' + DUMMY_USER.intraId,
          { nickName: inputValue },
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
      } catch (e) {}
    };
    fetchData();
    window.location.reload();
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
          ></input>
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
