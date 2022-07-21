import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilValue } from 'recoil';
import { friendList } from 'types/profileTypes';
import { profileState } from 'utils/recoil/profileData';
import instance from 'utils/axios';
import 'styles/users/FriendTable.css';

function FriendTable() {
  const profileData = useRecoilValue(profileState);
  const [List, setList] = useState<friendList | null>(null);

  useEffect(() => {
    getData();
  }, [List?.friendList.length]);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/friend/` + profileData.nickName); // 로그인 후 처리
      setList(getAPI.data);
    } catch (e) {}
  };

  return (
    <div className='friend-table'>
      {List?.friendList.map((element, index) => (
        <div className='friend-row' key={index}>
          <Link to={`/users/${element.nickName}/mypage`}>
            <span>{element.nickName}</span>
          </Link>
          <span> {element.status}</span>
        </div>
      ))}
    </div>
  );
}

export default FriendTable;
