import { useRecoilState, useSetRecoilState } from 'recoil';
import { useLocation } from 'react-router-dom';
import { useEffect } from 'react';
import FriendList from 'components/users/FriendList';
import MatchList from 'components/users/MatchList';
import UserInfo from 'components/users/UserInfo';
import instance from 'utils/axios';
import { profileState } from 'utils/recoil/profileData';
import { loginState } from 'utils/recoil/login';
import { errorState } from 'utils/recoil/error';
import { errorType } from 'types/errorTypes';
import 'styles/users/MyPage.css';

function UserPage() {
  const setIsLoggedIn = useSetRecoilState(loginState);
  const setErrorMessage = useSetRecoilState(errorState);
  const [profileData, setProfileData] = useRecoilState(profileState);
  const location = useLocation();
  const currentUser = location.pathname.split('/')[2];

  useEffect(() => {
    const getData = async () => {
      try {
        const getAPI = await instance.get(`/users/` + currentUser + `/mypage`);
        setProfileData(getAPI.data);
      } catch (err) {
        const e = err as errorType;
        if (e.message === `Network Error`) {
          setErrorMessage('E500');
        } else if (e.response.status === 403) {
          alert('다시 로그인 해주세요!!');
          localStorage.removeItem('trans-token');
          setIsLoggedIn(false);
          window.location.replace('/');
        } else setErrorMessage('UD01');
      }
    };
    getData();
  }, [currentUser, setProfileData]);

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
