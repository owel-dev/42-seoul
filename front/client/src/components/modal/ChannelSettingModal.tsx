import { socket } from 'components/layout/Layout';
import { useState } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';

function ChannelSettingModal() {
  const [channelId] = useRecoilState(channelState);
  const setModalInfo = useSetRecoilState(modalState);
  const [inputValue, setInputValue] = useState('');

  function CloseModal() {
    setModalInfo({ modalName: null });
  }
  function ChangePassword() {
    socket.emit('change-password', {
      password: inputValue,
      channelId: channelId.channelId,
    });
    CloseModal();
  }

  return (
    <div className='modal'>
      <div className='modal-title'>channel setting</div>
      <div className='modal-content'>
        <div>
          <span>비밀번호 </span>
          <input
            placeholder={'비밀번호 입력'}
            onChange={(e) => setInputValue(e.target.value)}
          />{' '}
        </div>
      </div>
      <div className='modal-select'>
        <button onClick={ChangePassword}>change</button>
        <button onClick={CloseModal}>close</button>
      </div>
    </div>
  );
}

export default ChannelSettingModal;
