import { useEffect } from 'react';
import { useSetRecoilState, useRecoilState } from 'recoil';
import ChannelList from 'components/lobby/ChannelList';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { chatListState } from 'utils/recoil/chat';
import { socket } from 'components/layout/Layout';
import 'styles/Lobby/Lobby.css';

function Lobby() {
  const setModalInfo = useSetRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const setChatList = useSetRecoilState(chatListState);

  const openGameModal = () => {
    setModalInfo({ modalName: 'MAIN-START' });
  };

  useEffect(() => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      setChatList([]);
      socket.emit('leave-channel');
    }
    setModalInfo({ modalName: null });
  }, []);

  return (
    <div className='lobby'>
      <div id='lobbyTitle'>Lobby</div>
      <button onClick={openGameModal} id='gameStart'>
        Game Start
      </button>
      <ChannelList />
    </div>
  );
}
export default Lobby;
