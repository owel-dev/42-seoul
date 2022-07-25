import io from 'socket.io-client';
import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import 'styles/layout/Content.css';

export const socket = io(
  `http://10.19.236.57:3000?token=${window.localStorage.getItem('trans-token')}`
);

type LayoutProps = {
  children: React.ReactNode;
};

function Layout({ children }: LayoutProps) {
  return (
    <div>
      <Nav />
      <Side />
      <div className='content'>{children}</div>
    </div>
  );
}

export default Layout;
