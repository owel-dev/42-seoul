import { Link } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { channelTypes } from 'types/LobbyTypes';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import 'styles/Lobby/Lobby.css';

function ChannelListRow({ props }: { props: channelTypes }) {
  const { channelId, player1, player2, curNumUser, password } = props;
  const setModalInfo = useSetRecoilState(modalState);
  const setChannelInfo = useSetRecoilState(channelState);

  function spectateRequest() {
    setChannelInfo({
      channelId: channelId,
      firstPlayer: player1,
      secondPlayer: player2,
    });
    socket.emit('spectate-request', { channelId: channelId });
  }
  function activePasswordSubmitModal() {
    setChannelInfo({
      channelId: channelId,
      firstPlayer: player1,
      secondPlayer: player2,
    });
    setModalInfo({ modalName: 'GAME-PASSWORD' });
  }

  return (
    <div className='channelListRow'>
      {password !== '' ? (
        <span onClick={activePasswordSubmitModal} className='rowFirstElement'>
          입장{' '}
        </span>
      ) : (
        <Link to={'/channel/' + channelId} className='rowFirstElement'>
          <span onClick={spectateRequest} className='rowFirstElement'>
            입장{' '}
          </span>
        </Link>
      )}
      <span className='rowElseElement'>player1 : {player1} </span>
      <span className='rowElseElement'>player2 : {player2} </span>
      <span className='blank'></span>
      <span className='rowElseElement'>
        비밀방 :{password ? <span>🔒</span> : <></>}
      </span>
    </div>
  );
}

export default ChannelListRow;
