import { Link } from 'react-router-dom';
import './Nav.css';

function Nav(){
    return (
        <div>
            <header className="nav">
            <Link to="home" className='link'>
                <button className='nav_menu'>logo</button>
            </Link>
            <span className='nav_menu' id="blank"></span>
            <Link to="ranking" className='link'>
                <button className='nav_menu'>rank</button>
            </Link>
            <button className='nav_menu'>mypage</button>
            <button className='nav_menu'>logout</button>
        </header>
        </div>
    )
}
export default Nav;