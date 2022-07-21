import { useEffect } from 'react';
import { useRecoilState } from 'recoil';
import { useLocation } from 'react-router-dom';
import { profileType } from 'types/profileTypes';
import { profileState } from 'utils/recoil/profileData';
import FriendList from 'components/users/FriendList';
import MatchList from 'components/users/MatchList';
import UserInfo from 'components/users/UserInfo';
import instance from 'utils/axios';
import 'styles/users/MyPage.css';

function UserPage() {
  const [profileData, setProfileData] =
    useRecoilState<profileType>(profileState);
  const location = useLocation();
  const currentUser = location.pathname.split('/')[2];

  useEffect(() => {
    const getData = async () => {
      try {
        const getAPI = await instance.get(`/users/` + currentUser + `/mypage`);
        setProfileData(getAPI.data);
      } catch (e) {}
    };
    getData();
  }, [currentUser]);

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
