import FriendList from 'components/users/FriendList';
import MatchList from 'components/users/MatchList';
import UserInfo from 'components/users/UserInfo';
import 'styles/users/MyPage.css';

function MyPage() {
  return (
    <div className='my-page'>
      <UserInfo />
      <div id='list'>
        <MatchList />
        <FriendList />
      </div>
    </div>
  );
}

export default MyPage;
