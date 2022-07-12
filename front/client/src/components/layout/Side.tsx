import 'styles/layout/Side.css';
import React from 'react';
import { io } from 'socket.io-client';

// const socket = io('http://10.19.226.233:3000');
// const SocketContext = React.createContext('');

function Side() {
  // socket.on('connect', () => {
  //   console.log('connect');
  // });

  // socket.on('hello', (data: string) => {
  //   console.log(data);
  // });

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
        <div className='userList'>유저리스트</div>
      </section>
      <section className='chatContainer'>
        <div className='chat'>채팅창</div>
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
