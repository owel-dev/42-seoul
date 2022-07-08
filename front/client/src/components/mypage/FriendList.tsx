import FriendTable from 'components/mypage/FriendTable'
import 'styles/mypage/FriendList.css'

function FriendList(){
    return (
        <div className='friend-list'>
            <h3>Friends</h3>
            <FriendTable />
        </div>
    );
}

export default FriendList;