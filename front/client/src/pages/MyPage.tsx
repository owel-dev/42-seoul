import FriendList from "components/mypage/FriendList";
import MatchList from "components/mypage/MatchList";
import UserInfo from "components/mypage/UserInfo";
import 'styles/mypage/MyPage.css'

function MyPage(){
    return (
    <div className="my-page">
        <UserInfo />
        <div id="list">
            <MatchList />
            <FriendList />
        </div>
    </div>);
}

export default MyPage;