import { Link } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { socket } from './Layout';
import 'styles/layout/Nav.css';

function Nav(props: { nickName: string; avatar: string }) {
  const setModalInfo = useSetRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);

  const exitChannel = () => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      socket.emit('join-channel', { channelId: '0' });
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
            onClick={exitChannel}
          />
        </Link>
        <div id='blank' />
        <Link to='/ranking'>
          <img
            src='/ranking.png'
            alt='rankImg'
            id='ranking'
            onClick={exitChannel}
          />
        </Link>
        <Link to={`/users/${props.nickName}/mypage`} id='avatar'>
          <img
            src={props.avatar}
            height='60vh'
            width='75vw'
            alt='avatar'
            id='avatar-image'
            onClick={exitChannel}
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
