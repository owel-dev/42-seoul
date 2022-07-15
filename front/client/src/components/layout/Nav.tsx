import { Link } from 'react-router-dom';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'types/modal';
import 'styles/layout/Nav.css';

function Nav() {
  const setModalInfo = useSetRecoilState(modalState);

  return (
    <div>
      <header className='nav'>
        <Link to='/' className='link'>
          <button className='nav_menu'>logo</button>
        </Link>
        <span className='nav_menu' id='blank'></span>
        <Link to='/ranking' className='link'>
          <button className='nav_menu'>rank</button>
        </Link>
        <Link to='/mypage' className='link'>
          <button className='nav_menu'>mypage</button>
        </Link>
        <button
          className='nav_menu'
          onClick={() => setModalInfo({ modalName: 'LOGOUT' })}
        >
          logout
        </button>
      </header>
    </div>
  );
}
export default Nav;
