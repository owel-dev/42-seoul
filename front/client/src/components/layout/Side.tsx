import UserList from './UserList';
import ChatList from './ChatList';
import 'styles/layout/Side.css';

function Side() {
  function send_massage() {
    // console.log(socket);
    // socket.emit('addChatContent', 'test');
    // socket.on('addChatContent', (data: any) => {
    //   console.log(data);
    // });
  }

  return (
    <aside className='side'>
      <section className='userContainer'>
        <div className='userTitle'>유저리스트</div>
        <div className='users'>
          <UserList />
        </div>
      </section>
      <section className='chatContainer'>
        <div className='chatTiTle'>채팅창</div>
        <div className='chat'>
          <ChatList />
        </div>
        <div className='messageContainer'>
          <input className='message' />
          <input
            type='button'
            value='보내기'
            className='button'
            onClick={send_massage}
          />
        </div>
      </section>
    </aside>
  );
}

export default Side;
