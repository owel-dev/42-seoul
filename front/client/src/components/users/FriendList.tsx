import FriendTable from 'components/users/FriendTable';
import 'styles/users/FriendList.css';

function FriendList() {
  return (
    <div className='friend-list'>
      <h3>Friends</h3>
      <FriendTable />
    </div>
  );
}

export default FriendList;
