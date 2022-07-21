import { useEffect } from 'react';
import { useRecoilState } from 'recoil';
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
  const currentPath = window.location.pathname;

  useEffect(() => {
    const getData = async () => {
      try {
        const getAPI = await instance.get(
          `/users/` + currentPath.split('/')[2] + `/mypage`
        );
        setProfileData(getAPI.data);
      } catch (e) {}
    };
    getData();
  }, [currentPath]);

  return (
    <>
      {profileData.intraId && (
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
