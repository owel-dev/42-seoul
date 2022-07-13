import Modal from 'components/modal/Modal';
import ProfileModal from 'components/modal/ProfileModal';
import { useSetRecoilState } from 'recoil';
import { profileModalState } from 'utils/recoil/modalState';

const dummy = ['aaa', 'bbb', 'ccc'];

function UserList() {
  const setStatus = useSetRecoilState(profileModalState);
  function ProfileModalOpen(nickName: string) {
    setStatus(nickName);
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
      <Modal>
        <ProfileModal />
      </Modal>
    </div>
  );
}
export default UserList;
