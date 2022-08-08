import { Link } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { friendState } from 'utils/recoil/friend';
import { chatListState } from 'utils/recoil/chat';
import 'styles/layout/Nav.css';

function Nav(props: { nickName: string; avatar: string }) {
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [friend, setFriend] = useRecoilState(friendState);
  const setModalInfo = useSetRecoilState(modalState);
  const setChatList = useSetRecoilState(chatListState);

  const movePage = () => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      setChatList([]);
      socket.emit('leave-channel');
    }
    if (friend) {
      setFriend(false);
      socket.emit('friend-end');
    }
  };

  return (
    <div>
      <header className='nav'>
        <Link to='/'>
          <img
            src='/42.png'
            width='80vw'
            alt='logoImg'
            id='logo'
            onClick={movePage}
          />
        </Link>
        <div id='blank' />
        <Link to='/ranking'>
          <img
            src='/ranking.png'
            alt='rankImg'
            id='ranking'
            onClick={movePage}
          />
        </Link>
        <Link to={`/users/${props.nickName}/mypage`} id='avatar'>
          <img
            src={props.avatar}
            height='60vh'
            width='75vw'
            alt='avatar'
            id='avatar-image'
            onClick={movePage}
          />
        </Link>
        <div>
          <img
            src='/logout.png'
            alt='logoutImg'
            id='logout'
            onClick={() => setModalInfo({ modalName: 'LOGOUT' })}
          />
        </div>
      </header>
    </div>
  );
}
export default Nav;
