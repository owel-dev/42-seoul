import { useEffect, useState } from 'react';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { socket } from 'components/layout/Layout';

type userListType = {
  nickName: string;
  admin: boolean;
};

function UserList() {
  const [userList, setUserList] = useState<userListType[]>();
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
          className='userList'
          onClick={() => ProfileModalOpen(element.nickName)}
        >
          {element.nickName}
          {element.admin && ' 👑'}
        </div>
      ))}
    </div>
  );
}

export default UserList;
