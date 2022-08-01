import { useEffect, useState } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { myDataState } from 'utils/recoil/myData';
import GameModule from 'components/game/GameModule';
import 'styles/game/Game.css';
import { Link } from 'react-router-dom';

function Game() {
  const setModalInfo = useSetRecoilState(modalState);
  const myData = useRecoilValue(myDataState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [admin, setAdmin] = useState<string>('');

  useEffect(() => {
    socket.on('admin-changed', (data) => {
      setAdmin(data);
    });
  });

  useEffect(() => {
    setModalInfo({ modalName: null });
  }, [setModalInfo]);

  const exitChannel = () => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      socket.emit('leave-channel');
    }
  };

  return (
    <div className='game-area'>
      <div className='game-setting-area'>
        {admin === myData.nickName && (
          <button
            onClick={() => setModalInfo({ modalName: 'GAME-SETTING' })}
            className='game-setting'
          >
            Game Setting
          </button>
        )}
        <Link to='/'>
          <button className='game-setting' onClick={exitChannel}>
            나가기
          </button>
        </Link>
      </div>
      <div className='player-game-area'>
        <div className='player'>
          <div>Player1</div>
          <div className='player-name'>{channelInfo.firstPlayer}</div>
        </div>
        <div className='game-content'>
          <GameModule />
        </div>
        <div className='player'>
          <div>Player2</div>
          <div className='player-name'>{channelInfo.secondPlayer}</div>
        </div>
      </div>
    </div>
  );
}
export default Game;
