import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilValue } from 'recoil';
import { friendList } from 'types/profileTypes';
import { profileState } from 'utils/recoil/profileData';
import instance from 'utils/axios';
import 'styles/users/FriendList.css';

function FriendTable() {
  const profileData = useRecoilValue(profileState);
  const [List, setList] = useState<friendList | null>(null);

  useEffect(() => {
    getData();
  }, [List?.friendList.length]);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/friend/` + profileData.nickName);
      setList(getAPI.data);
    } catch (e) {}
  };

  return (
    <div className='friendTable'>
      {List?.friendList.map((element, index) => (
        <div className='friendRow' key={index}>
          <Link
            to={`/users/${element.nickName}/mypage`}
            className='friendNickname'
          >
            <span>{element.nickName}</span>
          </Link>
          <span className='friendStatus'> {element.status}</span>
        </div>
      ))}
    </div>
  );
}

export default FriendTable;
