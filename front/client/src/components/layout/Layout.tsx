import io from 'socket.io-client';
import { useEffect, useState } from 'react';
import { useRecoilState } from 'recoil';
import { myDataState } from 'utils/recoil/myData';
import { myData } from 'types/myDataTypes';
import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import instance from 'utils/axios';
import SecondAuth from 'pages/SecondAuth';
import 'styles/layout/Content.css';

export let socket = io(
  `${process.env.REACT_APP_SERVERIP}?token=${window.localStorage.getItem(
    'trans-token'
  )}`
);

type LayoutProps = {
  children: React.ReactNode;
};

function Layout({ children }: LayoutProps) {
  const [myData, setMyData] = useRecoilState<myData>(myDataState);

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
  }, []);

  const [loading, setLoading] = useState<boolean>(false);

  const getMyData = async () => {
    try {
      const res = await instance.get(`/users/navi`);
      setMyData(res?.data);
      setLoading(true);
    } catch (e) {}
  };

  return myData?.isSecondAuth ? (
    <div>
      <Nav nickName={myData?.nickName} avatar={myData?.avatar} />
      <Side />
      <div className='content'>{children}</div>
    </div>
  ) : loading ? (
    <div>
      <SecondAuth />
    </div>
  ) : (
    <div>로딩중입니다</div>
  );
}

export default Layout;
