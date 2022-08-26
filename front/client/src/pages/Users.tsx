import { useEffect } from 'react';
import { useLocation } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { profileState } from 'utils/recoil/profileData';
import { loginState } from 'utils/recoil/login';
import { errorState } from 'utils/recoil/error';
import { errorType } from 'types/errorTypes';
import { socket } from 'components/layout/Layout';
import instance from 'utils/axios';
import refreshToken from 'utils/token';
import FriendList from 'components/users/FriendList';
import MatchList from 'components/users/MatchList';
import UserInfo from 'components/users/UserInfo';
import { modalState } from 'utils/recoil/modal';
import { channelState } from 'utils/recoil/gameState';
import { chatListState } from 'utils/recoil/chat';
import 'styles/users/MyPage.css';

function UserPage() {
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const setErrorMessage = useSetRecoilState(errorState);
  const [profileData, setProfileData] = useRecoilState(profileState);
  const location = useLocation();
  const currentUser = location.pathname.split('/')[2];
  const setModalInfo = useSetRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const setChatList = useSetRecoilState(chatListState);


  const logout = () => {
    socket.emit('logout', () => {
      socket.disconnect();
    });
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
  };

  useEffect(() => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      setChatList([]);
      socket.emit('leave-channel');
    }
    setModalInfo({ modalName: null });
  }, []);

  useEffect(() => {
    getData();
  }, [currentUser]);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/users/` + currentUser + `/mypage`);
      setProfileData(getAPI.data);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.status === 403) {
        logout();
      } else if (e.response.data.statusCode === 401) {
        refreshToken()
          .then(() => {
            if (isLoggedIn === true) getData();
          })
          .catch(() => {
            logout();
          });
      } else setErrorMessage('UD01');
    }
  };

  return (
    <>
      {profileData.nickName === currentUser && (
        <div className='my-page'>
          <UserInfo />
          <div id='list'>
            <MatchList />
            <FriendList />
          </div>
        </div>
      )}
    </>
  );
}

export default UserPage;
