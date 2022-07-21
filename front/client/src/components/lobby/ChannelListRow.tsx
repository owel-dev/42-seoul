import { socket } from 'App';
import { Link } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import { channelTypes } from 'types/LobbyTypes';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';

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
    socket.emit('spectate-request', { gameId: channelId });
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
    <div className='channel-list-row'>
      {password !== '' ? (
        <span
          style={{ backgroundColor: '#ffff66' }}
          onClick={activePasswordSubmitModal}
        >
          입장{' '}
        </span>
      ) : (
        <Link to={'/channel/' + channelId}>
          <span
            style={{ backgroundColor: '#ffff66' }}
            onClick={spectateRequest}
          >
            입장{' '}
          </span>
        </Link>
      )}
      <span>player1 : {player1} </span>
      <span>player2 : {player2} </span>
      <span>Headcount : {curNumUser} </span>
      <span>비밀방 : </span>
      {password ? <span>🔒</span> : <></>}
    </div>
  );
}

export default ChannelListRow;
