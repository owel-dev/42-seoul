import { useSetRecoilState } from 'recoil';
import { modalState } from 'types/modal';

const dummy = ['aaa', 'bbb', 'ccc'];

function UserList() {
  const setModalInfo = useSetRecoilState(modalState);

  function ProfileModalOpen(nickName: string) {
    setModalInfo({ modalName: 'SIDE-USER', user: nickName });
  }

  return (
    <div>
      {dummy.map((element, index) => {
        return (
          <div
            key={index}
            className='userlist-row'
            onClick={() => ProfileModalOpen(element)}
          >
            {element}
          </div>
        );
      })}
    </div>
  );
}

export default UserList;
