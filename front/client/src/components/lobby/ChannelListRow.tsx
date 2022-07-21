import { channelTypes } from 'types/LobbyTypes';

function ChannelListRow({ props }: { props: channelTypes }) {
  const { channelId, player1, player2, curNumUsers, password } = props;

  return (
    <div className='channel-list-row'>
      <a href={'/game/' + channelId}>
        <span style={{ backgroundColor: '#ffff66' }}>{channelId} </span>
      </a>
      <span>player1 : {player1} </span>
      <span>player2 : {player2} </span>
      <span>Headcount : {curNumUsers} </span>
      {password ? <span>🔒</span> : <></>}
    </div>
  );
}

export default ChannelListRow;
