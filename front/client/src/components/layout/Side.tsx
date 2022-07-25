import { useState, useEffect, useRef, useCallback } from 'react';
import { useRecoilValue } from 'recoil';
import { socket } from 'components/layout/Layout';
import { myDataState } from 'utils/recoil/myData';
import { chat } from 'types/chatTypes';
import UserList from './UserList';
import ChatList from './ChatList';
import 'styles/layout/Side.css';

function Side() {
  const myData = useRecoilValue(myDataState);
  const chatScroll = useRef<HTMLInputElement>(null);
  const [message, setMessage] = useState('');
  const [scrollState, setScrollState] = useState(true); // 자동 스크롤 여부
  const [chatList, setChatList] = useState<chat[]>([]); // 채팅 텍스트 list

  useEffect(() => {
    socket.on('message', (data) => {
      setChatList(chatList.concat(data));
    });
    if (chatScroll.current) {
      chatScroll.current.addEventListener('scroll', scroll);
      scrollToBottom();
    }
  });

  const sendMessgae = () => {
    if (message.length) {
      socket.emit('message', {
        nickName: myData.nickName,
        message: message,
        isDM: false,
      });
    }
    setMessage('');
  };

  const scrollToBottom = () => {
    if (chatScroll.current && scrollState) {
      const { scrollHeight, clientHeight } = chatScroll.current;
      chatScroll.current.scrollTo({
        top: scrollHeight - clientHeight,
        behavior: 'smooth',
      });
    }
  };

  const scrollEvent = () => {
    if (chatScroll.current) {
      const scrollTop = chatScroll.current.scrollTop; // 스크롤 위치
      const clientHeight = chatScroll.current.clientHeight; // 요소의 높이
      const scrollHeight = chatScroll.current.scrollHeight; // 스크롤의 높이

      // 스크롤이 맨 아래에 있을때
      setScrollState(
        scrollTop + clientHeight >= scrollHeight - 70 ? true : false
      );
    }
  };

  const scroll = useCallback(scrollEvent, []);

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
        <div className='chat' ref={chatScroll}>
          <ChatList chatList={chatList} />
        </div>
        <div className='messageContainer'>
          <form
            onSubmit={(e) => {
              e.preventDefault();
              {
                message.length &&
                  socket.emit('message', {
                    nickName: myData.nickName,
                    message: message,
                  });
                setMessage('');
              }
            }}
          >
            <input
              className='message'
              value={message}
              onChange={(e) => setMessage(e.target.value)}
            />
            <input
              type='button'
              value='보내기'
              className='button'
              onClick={sendMessgae}
            />
          </form>
        </div>
      </section>
    </aside>
  );
}

export default Side;
