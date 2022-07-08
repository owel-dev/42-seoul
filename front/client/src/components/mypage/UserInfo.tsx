import 'styles/mypage/UserInfo.css'

const dummy = {
    user :
    {
        intraId : "hello",
        avatar : "https://upload.wikimedia.org/wikipedia/commons/2/2c/Rotating_earth_%28large%29.gif", 
        nickName : "hello",
        win : 5,
        lose : 5,
        winRate : "50%"
    }
}

function UserInfo() {
    return (
        <div className='user-info'>
            <div id='user-info-left'>
                <img src={dummy.user.avatar} id='avatar' alt='프로필사진'></img>
                <button>change</button>
            </div>
            <div id='user-info-right'>
                <div className='user-info-line'>
                    <span className='user-label'>intraID </span>
                    <span>{dummy.user.intraId}</span>
                </div>
                <div className='user-info-line'>
                    <span className='user-label'>nickname </span>
                    <input defaultValue={dummy.user.nickName}></input>
                    <span> </span>
                    <button>change</button>
                </div>
                <div className='user-info-line'>
                    <span>{dummy.user.win} </span>
                    <span>win </span>
                    <span>{dummy.user.lose} </span>
                    <span>lose </span>
                    <span>winRate : </span>
                    <span>{dummy.user.winRate} </span>
                </div>
            </div>
        </div>
    );
}

export default UserInfo;