import { socket } from 'App';
import { useEffect, useState } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { Navigate } from 'react-router-dom';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { myDataState } from 'utils/recoil/myData';
import { myData } from 'types/myDataTypes';
import RadioOption from 'components/modal/RadioOption';
import 'styles/modal/Modal.css';

function GameStartModal() {
  const [matchWait, setMatchWait] = useState<boolean>(false);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [inputValue, setInputValue] = useState('');
  const [radioValue, setRadioValue] = useState('none');
  const setModalInfo = useSetRecoilState(modalState);
  const myData = useRecoilValue<myData>(myDataState);

  function closeModal() {
    setModalInfo({ modalName: null });
  }

  function radioChange(value: string) {
    setRadioValue(value);
  }

  function matchRequest() {
    socket.emit('match-request', {
      mode: radioValue,
      username: myData.nickName,
      password: inputValue,
    });
    setMatchWait(true);
  }

  useEffect(() => {
    socket.on('game-wait', (data) => {
      setMatchWait(false);
      setChannelInfo(data);
    });
  }, [setChannelInfo]);

  return (
    <>
      {channelInfo.channelId ? (
        <Navigate to={'/channel/' + channelInfo.channelId} />
      ) : (
        <div className='modal'>
          <div className='modal-title'>game start</div>
          {!matchWait ? (
            <div className='modal-content'>
              <fieldset>
                <legend>game option</legend>
                <RadioOption radioChange={radioChange} value='none' />
                <RadioOption radioChange={radioChange} value='map' />
                <RadioOption radioChange={radioChange} value='power' />
              </fieldset>
              <div>
                <span>비밀번호 </span>
                <input
                  placeholder={'비밀번호 입력'}
                  onChange={(e) => setInputValue(e.target.value)}
                />
              </div>
            </div>
          ) : (
            <div className='modal-content'>
              <div>대기중입니다..</div>
            </div>
          )}
          <div className='modal-select'>
            <button onClick={matchRequest}>regist</button>
            <button onClick={closeModal}>close</button>
          </div>
        </div>
      )}
    </>
  );
}

export default GameStartModal;
