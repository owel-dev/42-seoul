import { useState, useEffect, useRef, useCallback } from 'react';
import { useRecoilState, useRecoilValue } from 'recoil';
import { socket } from 'components/layout/Layout';
import { messageState, chatListState } from 'utils/recoil/chat';
import { myDataState } from 'utils/recoil/myData';
import UserList from 'components/layout/UserList';
import ChatList from 'components/layout/ChatList';
import 'styles/layout/Side.css';

function Side() {
  const chatScroll = useRef<HTMLInputElement>(null);
  const chatInput = useRef<HTMLInputElement>(null);
  const myData = useRecoilValue(myDataState);
  const [message, setMessage] = useRecoilState(messageState);
  const [chatList, setChatList] = useRecoilState(chatListState); // 채팅 텍스트 list
  const [scrollState, setScrollState] = useState(true); // 자동 스크롤 여부

  useEffect(() => {
    if (message.length) chatInput.current?.focus();
  }, [message]);

  useEffect(() => {
    socket.on('message', (data) => {
      setChatList(chatList.concat(data));
    });
    if (chatScroll.current) {
      chatScroll.current.addEventListener('scroll', scroll);
      scrollToBottom();
    }
  }, [chatList]);

  const sendMessage = () => {
    if (message.indexOf('#') === 0 && message.indexOf(' ') !== -1) {
      socket.emit('direct-message', {
        nickName: message.slice(1, message.indexOf(' ')),
        message: message.slice(message.indexOf(' ') + 1),
      });
    } else if (message.length) {
      socket.emit('message', {
        nickName: myData.nickName,
        message: message,
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
              sendMessage();
              setMessage('');
            }}
          >
            <div className='sendMessage'>
              <input
                className='message'
                value={message}
                ref={chatInput}
                onChange={(e) => setMessage(e.target.value)}
              />
              <input
                type='button'
                value='보내기'
                className='button'
                onClick={sendMessage}
              />
            </div>
          </form>
        </div>
      </section>
    </aside>
  );
}

export default Side;
