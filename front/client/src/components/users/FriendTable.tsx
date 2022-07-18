import axios from 'axios';
import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { friendList } from 'types/profileTypes';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import 'styles/users/FriendTable.css';

function FriendTable() {
  const [List, setList] = useState<friendList | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(
          DUMMY_SERVER + '/friend/' + DUMMY_USER.intraId,
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
  }, [List?.friendList.length]);

  return (
    <div className='friend-table'>
      {List?.friendList.map((element, index) => (
        <div className='friend-row' key={index}>
          <Link to={`/users/yongwkim`}>
            <span>{element.nickName}</span>
          </Link>
          <span> {element.status}</span>
        </div>
      ))}
    </div>
  );
}

export default FriendTable;
