import { Link } from 'react-router-dom';
import { useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { myData } from 'types/myDataTypes';
import instance from 'utils/axios';
import 'styles/layout/Nav.css';

function Nav() {
  const setModalInfo = useSetRecoilState(modalState);
  const [myData, setMyData] = useRecoilState<myData>(myDataState);

  useEffect(() => {
    getMyData();
  }, []);

  const getMyData = async () => {
    try {
      const res = await instance.get(`/users/navi`);
      setMyData(res?.data);
    } catch (e) {}
  };

  return (
    <div>
      {myData.nickName && (
        <header className='nav'>
          <a href='/' className='logo'>
            <img src='42.png' width='80vw' />
          </a>
          <div className='blank'>
            <a href='/ranking'>
              <div className='ranking'>🏆</div>
            </a>
          </div>
          <a href={`/users/${myData?.nickName}/mypage`} className='myPage'>
            <img src={myData?.avatar} height='60vh' width='75vw' />
          </a>
          <div
            className='logout'
            onClick={() => setModalInfo({ modalName: 'LOGOUT' })}
          >
            logout
          </div>
        </header>
      )}
    </div>
  );
}
export default Nav;
