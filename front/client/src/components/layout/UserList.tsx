import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';

const dummy = ['yongwkim', 'samin', 'ulee', 'jeonhyun'];

function UserList() {
  const setModalInfo = useSetRecoilState(modalState);

  function ProfileModalOpen(nickName: string) {
    setModalInfo({ modalName: 'SIDE-USER', user: nickName });
  }

  return (
    <div>
      {dummy.map((element, index) => (
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
