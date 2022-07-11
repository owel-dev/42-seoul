import 'styles/layout/Side.css';

function Side() {
  return (
    <aside className='side'>
      <section className='userContainer'>
        <div className='userList'>유저리스트</div>
      </section>
      <section className='chatContainer'>
        <div className='chat'>채팅창</div>
        <div className='messageContainer'>
          <input className='message' />
          <input type='button' value='보내기' className='button' />
        </div>
      </section>
    </aside>
  );
}

export default Side;
