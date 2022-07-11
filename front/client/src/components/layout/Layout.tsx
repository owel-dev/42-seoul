import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import 'styles/layout/Content.css';

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
