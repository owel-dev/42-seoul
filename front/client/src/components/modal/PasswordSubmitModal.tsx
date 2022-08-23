import { useState } from 'react';
import { Navigate } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';

function PasswordSubmitModal() {
  const setModalInfo = useSetRecoilState(modalState);
  const [channelInfo] = useRecoilState(channelState);
  const [inputValue, setInputValue] = useState('');
  const [passwordCorrect, setPasswordCorrect] = useState(false);

  function closeModal() {
    setModalInfo({ modalName: null });
  }

  function submitPassword() {
    socket.emit(
      'spectate-password',
      { channelId: channelInfo.channelId, password: inputValue },
      (data: boolean) => {
        if (data === true) {
          setPasswordCorrect(true);
          socket.emit('spectate-request', { channelId: channelInfo.channelId });
        } else {
          alert('password가 틀렸습니다.');
        }
      }
    );
  }

  return passwordCorrect ? (
    <Navigate to={'/channel/' + channelInfo.channelId} />
  ) : (
    <div className='modal'>
      <div className='modalTitle'>비밀번호 제출</div>
      <div className='modalContent'>
        <div>
          <span>password </span>
          <input
            placeholder={'비밀번호 입력'}
            onChange={(e) => setInputValue(e.target.value)}
          />
        </div>
      </div>
      <div className='modalSelect'>
        <button onClick={submitPassword} className='modalButton'>
          제출
        </button>
        <button onClick={closeModal} className='modalButton'>
          close
        </button>
      </div>
    </div>
  );
}

export default PasswordSubmitModal;
