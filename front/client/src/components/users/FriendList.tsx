import FriendTable from 'components/users/FriendTable';
import 'styles/users/FriendList.css';

function FriendList() {
  return (
    <div className='friendList'>
      <div className='friendTitle'>Friends</div>
      <FriendTable />
    </div>
  );
}

export default FriendList;
