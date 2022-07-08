import 'styles/mypage/MatchTable.css'

const dummy = {
    matchList:
        [
            {
                player1 : "hello",
                player2 : "bye",
                playerScore1 : 7,
                playerScore2 : 4
            },
            {
                player1 : "hello",
                player2 : "zzz",
                playerScore1 : 6,
                playerScore2 : 5
            },
            {
                player1 : "hello",
                player2 : "qapla",
                playerScore1 : 2,
                playerScore2 : 9
            }
        ]
};

function MatchTable(){
    return (
        <div className='match-table'>
            {dummy.matchList.map((element) => {
                return (
                    <div className='match-row'>
                        <span>{element.player1} </span>
                        <span>{element.playerScore1}</span>
                        <span> vs </span>
                        <span>{element.player2} </span>
                        <span>{element.playerScore2}</span>
                    </div>
                );
            })}
            
        </div>
    );
}
export default MatchTable;