import { useEffect } from 'react';
import { useLocation } from 'react-router-dom';
import { useRecoilState, useSetRecoilState } from 'recoil';
import instance from 'utils/axios';
import refreshToken from 'utils/token';
import { profileState } from 'utils/recoil/profileData';
import { loginState } from 'utils/recoil/login';
import { errorState } from 'utils/recoil/error';
import { errorType } from 'types/errorTypes';
import FriendList from 'components/users/FriendList';
import MatchList from 'components/users/MatchList';
import UserInfo from 'components/users/UserInfo';
import 'styles/users/MyPage.css';

function UserPage() {
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const setErrorMessage = useSetRecoilState(errorState);
  const [profileData, setProfileData] = useRecoilState(profileState);
  const location = useLocation();
  const currentUser = location.pathname.split('/')[2];

  const logout = () => {
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
  };

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
