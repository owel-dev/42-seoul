import 'styles/mypage/FriendTable.css'

const dummy = {
    friendList:
        [
            {
                nickName : "kim",
                status : "online"
            },
            {
                nickName : "lee",
                status : "offline"
            }, 
            {
                nickName : "park",
                status : "online"
            }, 
            {
                nickName : "choi",
                status : "ingame"
            }
]
};


function FriendTable() {
    return (
        <div className='friend-table'>
            {dummy.friendList.map((element) => {
                return (
                    <div className='friend-row'>
                        <span>{element.nickName} </span>
                        <span>{element.status}</span>
                    </div>
                );
            })}
            
        </div>
    );
}

export default FriendTable;