import { socket } from 'App';
import { useState } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { channelIdState } from 'utils/recoil/modalState';

function ChannelSettingModal() {
  const channelId = useRecoilState(channelIdState);
  const setModalInfo = useSetRecoilState(modalState);
  const [inputValue, setInputValue] = useState('');

  function CloseModal() {
    setModalInfo({ modalName: null });
  }
  function ChangePassword() {
    console.log(typeof inputValue);
    console.log(typeof channelId[0]);
    socket.emit('change-password', {
      password: inputValue,
      channelId: channelId[0],
    }); //채널Id 추가
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
