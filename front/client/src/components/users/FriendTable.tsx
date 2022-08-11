import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { friendList } from 'types/profileTypes';
import { friendState } from 'utils/recoil/friend';
import { profileState } from 'utils/recoil/profileData';
import { modalState } from 'utils/recoil/modal';
import 'styles/users/FriendList.css';

function FriendTable() {
  const profileData = useRecoilValue(profileState);
  const setFriend = useSetRecoilState(friendState);
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const [list, setList] = useState<friendList | null>(null);

  function spectateRequest(channelId: string) {
    socket.emit('spectate-request', { channelId: channelId });
  }
  const sendInvite = () => {
    setModalInfo({ modalName: 'GAME-INVITE', user: modalInfo.user });
  };

  useEffect(() => {
    socket.on('friend', (data) => {
      if (list !== data) setList(data);
    });
    setFriend(true);
    socket.emit('friend-start', profileData.nickName);
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

          {element.status === 'gaming' && (
            <Link to={'/channel/' + element.channelId}>
              <button
                className='friendButton'
                onClick={() => spectateRequest(element.channelId)}
              >
                관전하기
              </button>
            </Link>
          )}
          {element.status === 'online' && (
            <button className='friendButton' onClick={sendInvite}>
              같이하기
            </button>
          )}
          <span className='friendStatus'> {element.status}</span>
        </div>
      ))}
    </div>
  );
}

export default FriendTable;
