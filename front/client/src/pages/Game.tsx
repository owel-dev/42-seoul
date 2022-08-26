import { useEffect, useState } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { channelState, matchState } from 'utils/recoil/gameState';
import { myDataState } from 'utils/recoil/myData';
import { chatListState } from 'utils/recoil/chat';
import GameModule from 'components/game/GameModule';
import 'styles/game/Game.css';

type gameInfoType = {
  gameMode: string;
  firstPlayer: string;
  secondPlayer: string;
};

function Game() {
  const setModalInfo = useSetRecoilState(modalState);
  const setChatList = useSetRecoilState(chatListState);
  const myData = useRecoilValue(myDataState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [matchWait, setMatchWait] = useRecoilState(matchState);
  const [gameInfo, setGameInfo] = useState<gameInfoType>({
    gameMode: '',
    firstPlayer: '',
    secondPlayer: '',
  });
  const navigate = useNavigate();

  useEffect(() => {
    socket.emit('match-cancel');
    setMatchWait(false);
    setChatList([]);
    setModalInfo({ modalName: null });
    if (channelInfo.channelId === '')
    {
      navigate('/');
    }
  }, []);

  useEffect(() => {
    setModalInfo({ modalName: null });
    socket.emit(
      'game-player-data',
      channelInfo.channelId,
      (data: gameInfoType) => {
        setGameInfo(data);
      }
    );
  }, [myData]);

  const exitChannel = () => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      socket.emit('leave-channel');
    }
    setChatList([]);
  };

  return (
    <div style={{ width: '80vw' }}>
      {gameInfo.gameMode === '' ? (
        <></>
      ) : (
        <div className='game-area'>
          <div className='game-setting-area'>
            {myData.owner && (
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
              <div className='player-name'>{gameInfo.firstPlayer}</div>
            </div>
            <div className='game-content'>
              <GameModule gameMode={gameInfo.gameMode} />
            </div>
            <div className='player'>
              <div>Player2</div>
              <div className='player-name'>{gameInfo.secondPlayer}</div>
            </div>
          </div>
        </div>
      )}
    </div>
  );
}
export default Game;
