import io from 'socket.io-client';
import { useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { myDataState } from 'utils/recoil/myData';
import { myData } from 'types/myDataTypes';
import { loginState } from 'utils/recoil/login';
import { errorState } from 'utils/recoil/error';
import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import instance from 'utils/axios';
import SecondAuth from 'pages/SecondAuth';
import { modalState } from 'utils/recoil/modal';
import { inviteType } from 'types/GameTypes';
import { inviteState } from 'utils/recoil/gameState';
import 'styles/layout/Content.css';

export let socket = io();

type LayoutProps = {
  children: React.ReactNode;
};

function Layout({ children }: LayoutProps) {
  const [myData, setMyData] = useRecoilState<myData>(myDataState);
  const setIsLoggedIn = useSetRecoilState(loginState);
  const [errorMessage, setErrorMessage] = useRecoilState(errorState);
  const setModalInfo = useSetRecoilState(modalState);
  const setInviteData = useSetRecoilState<inviteType>(inviteState);

  useEffect(() => {
    if (socket.connected === false) {
      socket = io(
        `${process.env.REACT_APP_SERVERIP}?token=${window.localStorage.getItem(
          'trans-token'
        )}`
      );
    }
  }, []);

  useEffect(() => {
    if (!window.localStorage.getItem('trans-token')) {
      window.location.reload();
    }
  }, [socket]);

  useEffect(() => {
    getMyData();
    socket.on('together-request', (data) => {
      setInviteData(data);
      setModalInfo({ modalName: 'GAME-ACCEPT' });
    });
  }, []);

  const getMyData = async () => {
    try {
      const res = await instance.get(`/users/navi`);
      setMyData(res?.data);
    } catch (e: any) {
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.status === 403) {
        alert('다시 로그인 해주세요!!');
        localStorage.removeItem('trans-token');
        setIsLoggedIn(false);
        window.location.replace('/');
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
      <div className='content'>{children}</div>
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
