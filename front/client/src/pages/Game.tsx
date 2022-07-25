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
      <button onClick={() => setModalInfo({ modalName: 'GAME-SETTING' })}>
        채널설정
      </button>
      <div className='player-game-area'>
        <div className='player'>
          플레이어1
          <img
            src={'https://cdn.intra.42.fr/users/norminet.jpeg'}
            alt=''
            className='player-image'
          ></img>
          <label>{channelInfo.firstPlayer}</label>
        </div>
        <div className='game-content'>
          게임영역
          <GameModule />
        </div>
        <div className='player'>
          플레이어2
          <img
            src={'https://cdn.intra.42.fr/users/norminet.jpeg'}
            alt=''
            className='player-image'
          ></img>
          <label>{channelInfo.secondPlayer}</label>
        </div>
      </div>
    </div>
  );
}
export default Game;
