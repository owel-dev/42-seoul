import './Rank.css'

const userList : {[k: string]: any} = [
    {
        nickName : "aaa",
        wins : 6,
        loses : 1,
        winrate : 0.85
    },
    {
        nickName : "bbb",
        wins: 4,
        loses : 2,
        winrate : 0.5
    },
    {
        nickName : "ccc",
        wins: 2,
        loses : 3,
        winrate : 0.4
    },
    {
        nickName : "ddd",
        wins : 1,
        loses : 4,
        winrate : 0.2
    }
];



function RankTable() {
    userList.forEach((element : any, index : number) => {
        element.rank = index + 1;
    });
    return (
        <div className='rank-table'>
            <RankRow rank='rank' nickName='nickname' wins='win' loses='lose' winrate='winrate' type='rank-row-title'></RankRow>
            {userList.map((val: any, index: any) => {
                if (index % 2 === 1)
                    return (<RankRow rank={val.rank} nickName={val.nickName} wins={val.wins} loses={val.loses} winrate={val.winrate} type='rank-row-gray'></RankRow>)
                else
                    return (<RankRow rank={val.rank} nickName={val.nickName} wins={val.wins} loses={val.loses} winrate={val.winrate} type='rank-row'></RankRow>)
            })}
        </div>
    )
}

function RankRow(props : any) {
    return (
        <div className={props.type}>
            <span className='rank-cell'>{props.rank}</span>
            <span className='rank-cell'>{props.nickName}</span>
            <span className='rank-cell'>{props.wins}</span>
            <span className='rank-cell'>{props.loses}</span>
            <span className='rank-cell'>{props.winrate}</span>
        </div>
    )
}

function Rank() {
    return (
        <div className='rank'>
            <h1>ranking</h1>
            <RankTable></RankTable>
        </div>
    )
}
export default Rank;