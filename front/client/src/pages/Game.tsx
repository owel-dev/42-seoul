import axios from 'axios';
import { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { DUMMY_PLAYER, DUMMY_SERVER } from 'utils/dummy';
import GameModule from 'components/game/GameModule';
import 'styles/game/Game.css';

type playerType = {
  player1: string;
  player2: string;
};

function Game() {
  const { channelId } = useParams();

  const [players, setPlayers] = useState<playerType | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(DUMMY_SERVER + 'channel/' + channelId, {
          headers: {
            'Content-Type': 'application/json',
          },
        });
        setPlayers(getAPI.data);
      } catch (e) {}
    };
    fetchData();
  }, [channelId]);

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
          <label>{players?.player1}</label>
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
          <label>{players?.player2}</label>
        </div>
      </div>
    </div>
  );
}
export default Game;
