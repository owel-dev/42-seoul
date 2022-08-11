import { useEffect, useState } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';

type userListType = {
  nickName: string;
  owner: boolean;
  admin: boolean;
};

function UserList() {
  const [userList, setUserList] = useState<userListType[]>();
  const [myData, setMyData] = useRecoilState(myDataState);
  const setModalInfo = useSetRecoilState(modalState);

  useEffect(() => {
    socket.on('user-list', (data: userListType[]) => {
      setUserList(data);
      data.map((item) => {
        if (item.nickName === myData.nickName)
          setMyData((prev) => ({
            ...prev,
            owner: item.owner,
            admin: item.admin,
          }));
      });
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
          {element.owner && ' 👑'}
          {!element.owner && element.admin && ' 🎖'}
        </div>
      ))}
    </div>
  );
}

export default UserList;
