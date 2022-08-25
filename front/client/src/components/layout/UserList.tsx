import { useEffect, useState } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { loginState } from 'utils/recoil/login';

type userListType = {
  nickName: string;
  owner: boolean;
  admin: boolean;
};

function UserList() {
  const [userList, setUserList] = useState<userListType[]>();
  const [myData, setMyData] = useRecoilState(myDataState);
  const isLoggedIn = useRecoilValue(loginState);
  const setModalInfo = useSetRecoilState(modalState);

  useEffect(() => {
    socket.on('connected', () => {
      if (isLoggedIn) {
        socket.emit('user-list');
      }
    });
    socket.emit('user-list');
  }, []);

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
