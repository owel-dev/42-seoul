import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { friendList } from 'types/profileTypes';
import { friendState } from 'utils/recoil/friend';
import { profileState } from 'utils/recoil/profileData';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { channelState } from 'utils/recoil/gameState';
import 'styles/users/FriendList.css';

function FriendTable() {
  const profileData = useRecoilValue(profileState);
  const myData = useRecoilValue(myDataState);
  const setFriend = useSetRecoilState(friendState);
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const setChannelInfo = useSetRecoilState(channelState);
  const [list, setList] = useState<friendList | null>(null);

  function spectateRequest(channelId: string) {
    setChannelInfo((prev)=> ({...prev, channelId: channelId}));
    socket.emit('spectate-request', { channelId: channelId });
  }
  const sendInvite = (nickName: string) => {
    setModalInfo({ modalName: 'GAME-INVITE', user: nickName });
  };

  useEffect(() => {
    socket.on('friend', (data: friendList) => {
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

          {element.nickName !== myData.nickName && element.status === 'gaming' && (
            <Link to={'/channel/' + element.channelId}>
              <button
                className='friendButton'
                onClick={() => spectateRequest(element.channelId)}
              >
                관전하기
              </button>
            </Link>
          )}
          {element.nickName !== myData.nickName && element.status === 'online' && (
            <button
              className='friendButton'
              onClick={() => sendInvite(element.nickName)}
            >
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
