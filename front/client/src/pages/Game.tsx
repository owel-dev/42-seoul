import { useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import GameModule from 'components/game/GameModule';
import 'styles/game/Game.css';

function Game() {
  const setModalInfo = useSetRecoilState(modalState);
  const [channelInfo] = useRecoilState(channelState);

  useEffect(() => {
    setModalInfo({ modalName: null });
  }, [setModalInfo]);

  return (
    <div className='game-area'>
      <button
        onClick={() => setModalInfo({ modalName: 'GAME-SETTING' })}
        id='game-setting'
      >
        Game Setting
      </button>
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
