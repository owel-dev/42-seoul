import { useEffect } from 'react';
import RankTable from 'components/rank/RankTable';
import { socket } from 'components/layout/Layout';
import { useSetRecoilState, useRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { chatListState } from 'utils/recoil/chat';
import 'styles/rank/Rank.css';

function Rank() {
  const setModalInfo = useSetRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const setChatList = useSetRecoilState(chatListState);


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
    <div className='rank'>
      <div id='rank-title'>ranking</div>
      <RankTable />
    </div>
  );
}
export default Rank;
