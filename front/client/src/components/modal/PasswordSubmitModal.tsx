import { socket } from 'App';
import { useState } from 'react';
import { Navigate } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'types/modal';
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
      'submit-password',
      { channelId: channelInfo.channelId, password: inputValue },
      (data: boolean) => {
        if (data === true) {
          console.log('비밀번호가 맞았습니다');
          setPasswordCorrect(true);
          socket.emit('spectate-request', { gameId: channelInfo.channelId });
        } else {
          console.log('비밀번호가 틀렸습니다');
        }
      }
    );
  }
  if (passwordCorrect === true) {
    closeModal();
    return <Navigate to={'/channel/' + channelInfo.channelId} />;
  }
  return (
    <div className='modal'>
      <div className='modal-title'>비밀번호 제출</div>
      <div className='modal-content'>
        <div>
          <span>password </span>
          <input
            placeholder={'비밀번호 입력'}
            onChange={(e) => setInputValue(e.target.value)}
          />
        </div>
        {/* {passwordCorrect === true && (
          <Navigate to={'/channel/' + channelInfo.channelId} />
        )} */}
      </div>
      <div className='modal-select'>
        <button onClick={submitPassword}>제출</button>
        <button onClick={closeModal}>close</button>
      </div>
    </div>
  );
}

export default PasswordSubmitModal;
