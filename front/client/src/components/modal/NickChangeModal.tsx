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
        const getAPI = await axios.patch(
          DUMMY_SERVER + 'users/' + DUMMY_USER.intraId,
          {
            headers: {
              'Content-Type': 'application/json',
            },
            nickName: inputValue,
          }
        );
        // console.log(getAPI.data);
      } catch (e) {
        // console.log(e);
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
