import io from 'socket.io-client';
import { useEffect } from 'react';
import { useRecoilState } from 'recoil';
import { myDataState } from 'utils/recoil/myData';
import { myData } from 'types/myDataTypes';
import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import instance from 'utils/axios';
import SecondAuth from 'pages/SecondAuth';
import 'styles/layout/Content.css';

export const socket = io(
  `http://10.19.236.57:3000?token=${window.localStorage.getItem('trans-token')}`
);

type LayoutProps = {
  children: React.ReactNode;
};

function Layout({ children }: LayoutProps) {
  const [myData, setMyData] = useRecoilState<myData>(myDataState);

  useEffect(() => {
    console.log('test');
    getMyData();
  }, []);

  const getMyData = async () => {
    try {
      const res = await instance.get(`/users/navi`);
      setMyData(res?.data);
    } catch (e) {}
  };

  return myData?.isSecondAuth ? (
    <div>
      <Nav nickName={myData?.nickName} avatar={myData?.avatar} />
      <Side />
      <div className='content'>{children}</div>
    </div>
  ) : (
    <div>
      <SecondAuth />
    </div>
  );
}

export default Layout;
