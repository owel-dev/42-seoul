import { socket } from 'App';
import { Link } from 'react-router-dom';
import { channelTypes } from 'types/LobbyTypes';

function ChannelListRow({ props }: { props: channelTypes }) {
  const { channelId, player1, player2, curNumUsers, password } = props;

  function spectateRequest() {
    socket.emit('spectate-request', { gameId: channelId });
    //만약 비밀번호가 걸려있으면 모달 띄우고 비밀번호 일치해야 들어갈 수 있게 만들어야 함
  }
  //비밀번호가 !== null이면 link 대신에 모달을 ㄴ
  return (
    <div className='channel-list-row'>
      {/* <a href={'/game/' + channelId}>
        <span style={{ backgroundColor: '#ffff66' }}>{channelId} </span>
      </a> */}
      <Link to={'/channel/' + channelId} onClick={spectateRequest}>
        <span style={{ backgroundColor: '#ffff66' }}>입장 </span>
      </Link>
      <span>player1 : {player1} </span>
      <span>player2 : {player2} </span>
      <span>Headcount : {curNumUsers} </span>
      {password ? <span>🔒</span> : <></>}
    </div>
  );
}

export default ChannelListRow;
