import './Nav.css';

function Nav(){
    return (
        <div>
            <header className="nav">
            <button className='nav_menu'>logo</button>
            <span className='nav_menu' id="blank"></span>
            <button className='nav_menu'>rank</button>
            <button className='nav_menu'>mypage</button>
            <button className='nav_menu'>logout</button>
        </header>
        </div>
    )
}
export default Nav;