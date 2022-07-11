import 'styles/Lobby/ChannelList.css'

const dummy = {
    channelList:
        [
            {
                channelId: "#aaa",
                player1: "test",
                player2: "vvv",
                curNumUsers: 2,
                maxUser: 8,
                password: null,
            },
            {
                channelId: "#bbb",
                player1: "ppp",
                player2: "lll",
                curNumUsers: 5,
                maxUser: 8,
                password: "0000",
            }
        ]
}

function ChannelListRow(props : any){
    return (
        <div className='channel-list-row'>
            <span>{props.channelId} </span>
            <span>player1 : {props.player1} </span>
            <span>player2 : {props.player2} </span>
            <span>Headcount : {props.curNumUsers} </span>
            <span>{props.protect}</span>
    </div>
    );
}

function ChannelList(){
    return (
        <div>
            {dummy.channelList.map((element, index) => {
                const protect = element.password;
                if (protect === null)
                    return (<ChannelListRow key={index} channelId={element.channelId} player1={element.player1} player2={element.player2} curNumUsers={element.curNumUsers} protect=""></ChannelListRow>)
                else
                    return (<ChannelListRow key={index} channelId={element.channelId} player1={element.player1} player2={element.player2} curNumUsers={element.curNumUsers} protect="🔒"></ChannelListRow>)
            })}
        </div>
    );
}
export default ChannelList;