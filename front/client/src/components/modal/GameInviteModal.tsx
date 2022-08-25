import { useEffect, useState } from 'react';
import { useRecoilState, useRecoilValue } from 'recoil';
import { Navigate } from 'react-router-dom';
import { socket } from 'components/layout/Layout';
import { myData } from 'types/myDataTypes';
import { modalState } from 'utils/recoil/modal';
import { channelState, matchState } from 'utils/recoil/gameState';
import { myDataState } from 'utils/recoil/myData';
import RadioOption from 'components/modal/RadioOption';
import 'styles/modal/Modal.css';

function GameInviteModal() {
  const myData = useRecoilValue<myData>(myDataState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const [matchWait, setMatchWait] = useRecoilState(matchState);
  const [inputValue, setInputValue] = useState('');
  const [radioValue, setRadioValue] = useState('none');
  const [disable, SetDisable] = useState<boolean>(false);

  function closeModal() {
    if (matchWait === true) {
      socket.emit('match-cancel', modalInfo.user);
      setMatchWait(false);
    }
    setModalInfo({ modalName: null });
  }

  function radioChange(value: string) {
    setRadioValue(value);
  }

  function matchRequest() {
    SetDisable(true);
    socket.emit('together-request', {
      gameMode: radioValue,
      nickName: myData.nickName,
      password: inputValue,
      oppNickName: modalInfo.user,
    });

    setMatchWait(true);
  }

  useEffect(() => {
    let checkalert = false;
    socket.on('game-wait', (data) => {
      setMatchWait(false);
      setChannelInfo(data);
    });
    socket.on('match-cancel', () => {
      setMatchWait(false);
      if (checkalert === false) {
        alert(`${modalInfo.user}(이)가 같이하기를 취소하였습니다.`);
        checkalert = true;
      }
      setModalInfo({ modalName: null });
    });
  }, []);

  return (
    <>
      {channelInfo.channelId ? (
        <Navigate to={'/channel/' + channelInfo.channelId} />
      ) : (
        <div className='modal'>
          <div className='modalTitle'>게임 초대</div>
          {!matchWait ? (
            <div className='modalContent'>
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
            <div className='modalContent'>
              <div>대기중입니다..</div>
            </div>
          )}
          <div className='modalSelect'>
            <button
              disabled={disable}
              onClick={matchRequest}
              className='modalButton'
            >
              regist
            </button>
            <button onClick={closeModal} className='modalButton'>
              close
            </button>
          </div>
        </div>
      )}
    </>
  );
}

export default GameInviteModal;
