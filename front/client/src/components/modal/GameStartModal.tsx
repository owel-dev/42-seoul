import { socket } from 'App';
import { useState } from 'react';
import { Navigate } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import 'styles/modal/Modal.css';

function GameStartModal() {
  const setModalInfo = useSetRecoilState(modalState);
  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };
  const [radioValue, setRadioValue] = useState('none');
  const [matchWait, setMatchWait] = useState<boolean>(false);
  const [channelId, setChannelId] = useState<string | null>(null);
  const [inputValue, setInputValue] = useState('');

  function radioChange(value: string) {
    setRadioValue(value);
  }

  //1. 버튼 누르면 (라디오 버튼)정보를 가지고 서버에 전송
  //2. 서버는 받아서 ()한 처리를 하고 ()를 전송
  //3. 프론트는 () 응답이 올때까지 매칭 대기를 띄운다
  //4. 프론트에 () 응답이 도착하면 게임방으로 이동한다

  function matchRequest() {
    socket.emit('match-request', {
      mode: radioValue,
      username: 'jeonhyun',
      password: inputValue,
    });
    setMatchWait(true);

    socket.on('game-wait', (data) => {
      setMatchWait(false);
      setChannelId(data.channelId);
    });
  }
  if (channelId !== null) {
    CloseModal();
    return <Navigate to={'/channel/' + channelId} />;
  } else if (matchWait === false) {
    return (
      <div className='modal'>
        <div className='modal-title'>game start</div>
        <div className='modal-content'>
          <fieldset>
            <legend>game option</legend>
            <div>
              <input
                type='radio'
                name='drone'
                id='none'
                value='none'
                onChange={() => radioChange('none')}
              ></input>
              <label>none</label>
            </div>
            <div>
              <input
                type='radio'
                name='drone'
                id='map'
                value='map'
                onChange={() => radioChange('map')}
              ></input>
              <label>map option</label>
            </div>
            <div>
              <input
                type='radio'
                name='drone'
                id='power'
                value='power'
                onChange={() => radioChange('power')}
              ></input>
              <label>power option</label>
            </div>
          </fieldset>
          <div>
            <span>비밀번호 </span>
            <input
              placeholder={'비밀번호 입력'}
              onChange={(e) => setInputValue(e.target.value)}
            />
          </div>
        </div>
        <div className='modal-select'>
          <button onClick={matchRequest}>regist</button>
          <button onClick={CloseModal}>close</button>
        </div>
      </div>
    );
  } else {
    return (
      <div className='modal'>
        <div className='modal-title'>game start</div>
        <div className='modal-content'>
          <div>대기중입니다..</div>
        </div>
        <div className='modal-select'>
          <button onClick={matchRequest}>regist</button>
          <button onClick={CloseModal}>close</button>
        </div>
      </div>
    );
  }
}

export default GameStartModal;
