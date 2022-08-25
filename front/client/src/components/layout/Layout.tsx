import io from 'socket.io-client';
import { useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { myDataState } from 'utils/recoil/myData';
import { loginState } from 'utils/recoil/login';
import { errorState } from 'utils/recoil/error';
import { modalState } from 'utils/recoil/modal';
import { inviteState } from 'utils/recoil/gameState';
import { myData } from 'types/myDataTypes';
import { inviteType } from 'types/GameTypes';
import { errorType } from 'types/errorTypes';
import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import refreshToken from 'utils/token';
import instance from 'utils/axios';
import SecondAuth from 'pages/SecondAuth';
import 'styles/layout/Content.css';

export let socket = io();

type LayoutProps = {
  children: React.ReactNode;
};

function Layout({ children }: LayoutProps) {
  const [myData, setMyData] = useRecoilState<myData>(myDataState);
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const [errorMessage, setErrorMessage] = useRecoilState(errorState);
  const setModalInfo = useSetRecoilState(modalState);
  const setInviteData = useSetRecoilState<inviteType>(inviteState);

  useEffect(() => {
    if (socket.connected === false) {
      socket = io(
        `${
          process.env.REACT_APP_SERVERIP
        }?accessToken=${window.localStorage.getItem('accessToken')}`
      );
    }
    socket.on('together-request', (data) => {
      setInviteData(data);
      setModalInfo({ modalName: 'GAME-ACCEPT' });
    });
  }, []);

  const logout = () => {
    socket.emit('logout', () => {
      socket.disconnect();
    });
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
  };

  useEffect(() => {
    if (!window.localStorage.getItem('accessToken')) {
      window.location.reload();
    }
    getMyData();
  }, [socket]);

  const getMyData = async () => {
    try {
      const res = await instance.get(`/users/navi`);
      setMyData(res?.data);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.status === 403) {
        logout();
      } else if (e.response.data.statusCode === 401) {
        refreshToken()
          .then(() => {
            if (isLoggedIn === true) getMyData();
          })
          .catch(() => {
            logout();
          });
      } else setErrorMessage('NV01');
    }
  };

  return myData?.isSecondAuth ? (
    <div>
      {errorMessage === '' && (
        <>
          <Nav nickName={myData?.nickName} avatar={myData?.avatar} />
          <Side />
        </>
      )}
      <div className='contentSetting'>{children}</div>
    </div>
  ) : (
    <>
      {myData.nickName && (
        <div>
          <SecondAuth />
        </div>
      )}
    </>
  );
}

export default Layout;
