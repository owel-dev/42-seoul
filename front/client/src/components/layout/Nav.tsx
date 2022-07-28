import { Link } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import 'styles/layout/Nav.css';

function Nav(props: { nickName: string; avatar: string }) {
  const setModalInfo = useSetRecoilState(modalState);

  return (
    <div>
      <header className='nav'>
        <Link to='/'>
          <img src='/42.png' width='80vw' alt='logoImg' id='logo' />
        </Link>
        <div id='blank' />
        <Link to='/ranking'>
          <img src='/ranking.png' alt='rankImg' id='ranking'></img>
        </Link>
        <Link to={`/users/${props.nickName}/mypage`} id='avatar'>
          <img
            src={props.avatar}
            height='60vh'
            width='75vw'
            alt='avatar'
            id='avatar-image'
          />
        </Link>
        <div>
          <img
            src='/logout.png'
            alt='logoutImg'
            id='logout'
            onClick={() => setModalInfo({ modalName: 'LOGOUT' })}
          ></img>
        </div>
      </header>
    </div>
  );
}
export default Nav;
