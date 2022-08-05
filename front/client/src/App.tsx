import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import { RecoilRoot } from 'recoil';
import Layout from 'components/layout/Layout';
import ModalProvider from 'components/modal/ModalProvider';
import LoginChecker from 'components/LoginChecker';
import ErrorChecker from 'components/ErrorChecker';
import Rank from 'pages/Rank';
import UserPage from 'pages/Users';
import Lobby from 'pages/Lobby';
import Game from 'pages/Game';
import Error404 from 'pages/Error404';

function App() {
  return (
    <>
      <RecoilRoot>
        <Router>
          <LoginChecker>
            <ErrorChecker>
              <Layout>
                <Routes>
                  <Route path='/ranking' element={<Rank />} />
                  <Route
                    path='/users/:nickName/mypage'
                    element={<UserPage />}
                  />
                  <Route path='/' element={<Lobby />} />
                  <Route path='/channel/:channelId' element={<Game />} />
                  <Route path='*' element={<Error404 />} />
                </Routes>
              </Layout>
              <ModalProvider />
            </ErrorChecker>
          </LoginChecker>
        </Router>
      </RecoilRoot>
    </>
  );
}

export default App;
