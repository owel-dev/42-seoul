import { Link } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import 'styles/layout/Nav.css';

function Nav(props: { nickName: string; avatar: string }) {
  const setModalInfo = useSetRecoilState(modalState);

  return (
    <div>
      <header className='nav'>
        <Link to='/' className='logo'>
          <img src='/42.png' width='80vw' alt='logoImg' />
        </Link>
        <div className='blank'>
          <Link to='/ranking'>
            <div className='ranking'>🏆</div>
          </Link>
        </div>
        <Link to={`/users/${props.nickName}/mypage`} className='myPage'>
          <img src={props.avatar} height='60vh' width='75vw' alt='avatar' />
        </Link>
        <div
          className='logout'
          onClick={() => setModalInfo({ modalName: 'LOGOUT' })}
        >
          logout
        </div>
      </header>
    </div>
  );
}
export default Nav;
