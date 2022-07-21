import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { RecoilRoot } from 'recoil';
import io from 'socket.io-client';
import Layout from 'components/layout/Layout';
import Rank from 'pages/Rank';
import UserPage from 'pages/Users';
import Lobby from 'pages/Lobby';
import Game from 'pages/Game';
import ModalProvider from 'components/modal/ModalProvider';
import LoginChecker from 'components/LoginChecker';

export const socket = io('http://10.19.236.57:3000');

function App() {
  return (
    <>
      <RecoilRoot>
        <Router>
          <LoginChecker>
            <Layout>
              <Routes>
                <Route path='/ranking' element={<Rank />} />
                <Route path='/users/:nickName/mypage' element={<UserPage />} />
                <Route path='/' element={<Lobby />} />
                <Route path='/channel/:channelId' element={<Game />} />
              </Routes>
            </Layout>
            <ModalProvider />
          </LoginChecker>
        </Router>
      </RecoilRoot>
    </>
  );
}

export default App;
