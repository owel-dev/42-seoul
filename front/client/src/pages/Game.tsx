import { useEffect, useState } from 'react';
import { useParams } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import GameModule from 'components/game/GameModule';
import instance from 'utils/axios';
import { modalState } from 'utils/recoil/modal';
import { channelIdState } from 'utils/recoil/modalState';
import 'styles/game/Game.css';

type playerType = {
  player1: string;
  player2: string;
};

function Game() {
  const { channelId } = useParams();
  const setModalInfo = useSetRecoilState(modalState);

  const setSaveChannelId = useSetRecoilState(channelIdState);
  setSaveChannelId(channelId);

  const [players, setPlayers] = useState<playerType | null>(null);

  useEffect(() => {
    getData();
  }, []);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/channel/` + channelId);
      setPlayers(getAPI.data);
    } catch (e) {}
  };

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
          <label>{players?.player1}</label>
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
          <label>{players?.player2}</label>
        </div>
      </div>
    </div>
  );
}
export default Game;
