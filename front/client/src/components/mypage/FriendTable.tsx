import axios from 'axios';
import { useState, useEffect } from 'react';
import { friendList } from 'types/MyPageTypes';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import 'styles/mypage/FriendTable.css';

function FriendTable() {
  const [List, setList] = useState<friendList | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(
          DUMMY_SERVER + 'friend/' + DUMMY_USER.intraId,
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
        setList(getAPI.data);
      } catch (e) {}
    };
    fetchData();
  }, []);

  return (
    <div className='friend-table'>
      {List?.friendList.map((element, index) => {
        return (
          <div className='friend-row' key={index}>
            <span>{element.nickName} </span>
            <span>{element.status}</span>
          </div>
        );
      })}
    </div>
  );
}

export default FriendTable;
