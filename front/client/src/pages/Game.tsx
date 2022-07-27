import { useEffect, useState } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import GameModule from 'components/game/GameModule';
import 'styles/game/Game.css';
import { socket } from 'components/layout/Layout';
import { myDataState } from 'utils/recoil/myData';

function Game() {
  const setModalInfo = useSetRecoilState(modalState);
  const myData = useRecoilValue(myDataState);
  const [channelInfo] = useRecoilState(channelState);
  const [admin, setAdmin] = useState<string>('');

  useEffect(() => {
    socket.on('admin-changed', (data) => {
      setAdmin(data);
    });
  });

  useEffect(() => {
    setModalInfo({ modalName: null });
  }, [setModalInfo]);

  return (
    <div className='game-area'>
      {admin === myData.nickName && (
        <button
          onClick={() => setModalInfo({ modalName: 'GAME-SETTING' })}
          id='game-setting'
        >
          Game Setting
        </button>
      )}
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
