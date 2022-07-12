import { useState, useEffect } from 'react';
import axios from 'axios';
import 'styles/mypage/FriendTable.css';
import { friendList } from 'types/MyPageTypes';

// const dummy = {
//     friendList:
//         [
//             {
//                 nickName : "kim",
//                 status : "online"
//             },
//             {
//                 nickName : "lee",
//                 status : "offline"
//             },
//             {
//                 nickName : "park",
//                 status : "online"
//             },
//             {
//                 nickName : "choi",
//                 status : "ingame"
//             }
// ]
// };

const id = 'hello';

function FriendTable() {
  const [List, setList] = useState<friendList | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(
          'http://localhost:3000/' + 'friend/' + { id },
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
        setList(getAPI.data);
      } catch (e) {
        console.log(e);
      }
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
