import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { RecoilRoot } from 'recoil';
import Layout from 'components/layout/Layout';
import Rank from 'pages/Rank';
import MyPage from 'pages/Users';
import Lobby from 'pages/Lobby';
import Game from 'pages/Game';
import ModalProvider from 'components/modal/ModalProvider';

function App() {
  return (
    <>
      <RecoilRoot>
        <Router>
          <Layout>
            <Routes>
              <Route path='/ranking' element={<Rank />} />
              <Route path='/users/:nickName' element={<MyPage />} />
              <Route path='/' element={<Lobby />} />
              <Route path='/game/:channelId' element={<Game />} />
            </Routes>
          </Layout>
          <ModalProvider />
        </Router>
      </RecoilRoot>
    </>
  );
}

export default App;
