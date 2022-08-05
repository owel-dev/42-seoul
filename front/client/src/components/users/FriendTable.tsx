import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { friendList } from 'types/profileTypes';
import { friendState } from 'utils/recoil/friend';
import { profileState } from 'utils/recoil/profileData';
import 'styles/users/FriendList.css';

function FriendTable() {
  const profileData = useRecoilValue(profileState);
  const setFriend = useSetRecoilState(friendState);
  const [list, setList] = useState<friendList | null>(null);

  useEffect(() => {
    setFriend(true);
    socket.emit('friend-start', profileData.nickName);
  }, []);

  useEffect(() => {
    socket.on('friend', (data) => {
      if (list !== data) setList(data);
    });
  }, []);

  return (
    <div className='friendTable'>
      {list?.friendList.map((element, index) => (
        <div className='friendRow' key={index}>
          <Link
            to={`/users/${element.nickName}/mypage`}
            className='friendNickname'
          >
            <span
              onClick={() => {
                setFriend(false);
                socket.emit('friend-end');
              }}
            >
              {element.nickName}
            </span>
          </Link>
          <span className='friendStatus'> {element.status}</span>
        </div>
      ))}
    </div>
  );
}

export default FriendTable;
