import { socket } from 'App';
import { useEffect, useState } from 'react';
import { Navigate } from 'react-router-dom';
import { modalState } from 'utils/recoil/modal';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { channelState } from 'utils/recoil/gameState';
import 'styles/modal/Modal.css';
// import GameOption from 'components/game/GameOption';
// import GameMatchWait from 'components/game/GameMatchWait';

function GameStartModal() {
  const [matchWait, setMatchWait] = useState<boolean>(false);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [inputValue, setInputValue] = useState('');
  const [radioValue, setRadioValue] = useState('none');
  const setModalInfo = useSetRecoilState(modalState);
  function closeModal() {
    setModalInfo({ modalName: null });
  }

  function radioChange(value: string) {
    setRadioValue(value);
  }

  function matchRequest() {
    socket.emit('match-request', {
      mode: radioValue,
      username: 'jeonhyun',
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
  //게임 시작, 대기를 따로 컴포넌트로 빼기 GameOption, GameMatchWait

  if (channelInfo.channelId !== null) {
    return <Navigate to={'/channel/' + channelInfo.channelId} />;
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
          <button onClick={closeModal}>close</button>
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
          <button onClick={closeModal}>close</button>
        </div>
      </div>
    );
  }
  // return (
  //   <div>
  //     {channelInfo.channelId !== null && (
  //       <Navigate to={'/channel/' + channelInfo.channelId} />
  //     )}
  //     {matchWait === false && (
  //       // <GameOption
  //       //   radioChange={radioChange}
  //       //   setInputValue={setInputValue}
  //       //   matchRequest={matchRequest}
  //       //   closeModal={closeModal}
  //       // />
  //       <div className='modal'>
  //         <div className='modal-title'>game start</div>
  //         <div className='modal-content'>
  //           <fieldset>
  //             <legend>game option</legend>
  //             <div>
  //               <input
  //                 type='radio'
  //                 name='drone'
  //                 id='none'
  //                 value='none'
  //                 onChange={() => radioChange('none')}
  //               ></input>
  //               <label>none</label>
  //             </div>
  //             <div>
  //               <input
  //                 type='radio'
  //                 name='drone'
  //                 id='map'
  //                 value='map'
  //                 onChange={() => radioChange('map')}
  //               ></input>
  //               <label>map option</label>
  //             </div>
  //             <div>
  //               <input
  //                 type='radio'
  //                 name='drone'
  //                 id='power'
  //                 value='power'
  //                 onChange={() => radioChange('power')}
  //               ></input>
  //               <label>power option</label>
  //             </div>
  //           </fieldset>
  //           <div>
  //             <span>비밀번호 </span>
  //             <input
  //               placeholder={'비밀번호 입력'}
  //               onChange={(e) => setInputValue(e.target.value)}
  //             />
  //           </div>
  //         </div>
  //         <div className='modal-select'>
  //           <button onClick={matchRequest}>regist</button>
  //           <button onClick={closeModal}>close</button>
  //         </div>
  //       </div>
  //     )}
  //     {matchWait === true && (
  //       // <GameMatchWait matchRequest={matchRequest} closeModal={closeModal} />
  //       <div className='modal'>
  //         <div className='modal-title'>game start</div>
  //         <div className='modal-content'>
  //           <div>대기중입니다..</div>
  //         </div>
  //         <div className='modal-select'>
  //           <button onClick={matchRequest}>regist</button>
  //           <button onClick={closeModal}>close</button>
  //         </div>
  //       </div>
  //     )}
  //   </div>
  // );
}

export default GameStartModal;
