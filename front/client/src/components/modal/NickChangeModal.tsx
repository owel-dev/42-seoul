import { nickChangeModalState } from 'utils/recoil/modalState';
import { useRecoilState } from 'recoil';
import 'styles/modal/Modal.css';
import { useState } from 'react';
import axios from 'axios';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';

function NickChangeModal() {
  const [status, setStatus] = useRecoilState(nickChangeModalState);
  const [inputValue, setInputValue] = useState('');
  const CloseModal = () => {
    setStatus(false);
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
        console.log(getAPI.data);
      } catch (e) {
        console.log(e);
      }
    };
    fetchData();
  }
  if (status === false) return <div></div>;
  else
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
