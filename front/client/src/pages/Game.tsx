import { useEffect, useState } from 'react';
import { Link } from 'react-router-dom';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import GameModule from 'components/game/GameModule';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { myDataState } from 'utils/recoil/myData';
import { chatListState } from 'utils/recoil/chat';
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
  const [admin, setAdmin] = useState<string>('');
  const [gameInfo, setgameInfo] = useState<gameInfoType>({
    gameMode: '',
    firstPlayer: '',
    secondPlayer: '',
  });

  useEffect(() => {
    socket.on('admin-changed', (data) => {
      setAdmin(data);
    });
    setModalInfo({ modalName: null });
    setChatList([]);
    socket.emit(
      'game-player-data',
      channelInfo.channelId,
      (data: gameInfoType) => {
        setgameInfo(data);
      }
    );
  }, []);

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
    <div>
      {gameInfo.gameMode === '' ? (
        <></>
      ) : (
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
