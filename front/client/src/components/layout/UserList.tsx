import { socket } from 'components/layout/Layout';
import { useEffect, useState } from 'react';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';

function UserList() {
  const [userList, setUserList] = useState<string[]>();
  const setModalInfo = useSetRecoilState(modalState);

  useEffect(() => {
    socket.on('user-list', (data) => {
      setUserList(data);
    });
  });

  function ProfileModalOpen(nickName: string) {
    setModalInfo({ modalName: 'SIDE-USER', user: nickName });
  }

  return (
    <div>
      {userList?.map((element, index) => (
        <div
          key={index}
          className='userlist-row'
          onClick={() => ProfileModalOpen(element)}
        >
          {element}
        </div>
      ))}
    </div>
  );
}

export default UserList;
