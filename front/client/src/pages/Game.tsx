import GameModule from 'components/game/GameModule';
import 'styles/game/Game.css';
import { DUMMY_PLAYER } from 'utils/dummy';

function Game() {
  return (
    <div className='game-area'>
      <button>채널설정</button>
      <div className='player-game-area'>
        <div className='player'>
          플레이어1
          <img
            src={DUMMY_PLAYER.players[0].avatar}
            alt=''
            className='player-image'
          ></img>
          <label>{DUMMY_PLAYER.players[0].player}</label>
        </div>
        <div className='game-content'>
          게임영역
          <GameModule />
        </div>
        <div className='player'>
          플레이어2
          <img
            src={DUMMY_PLAYER.players[1].avatar}
            alt=''
            className='player-image'
          ></img>
          <label>{DUMMY_PLAYER.players[1].player}</label>
        </div>
      </div>
    </div>
  );
}
export default Game;
