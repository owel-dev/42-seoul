import axios from 'axios';
import React, {useState, useEffect} from 'react';
import './Rank.css'

type userRank = {
    ranking : [{
        rank: string;
        nickName: string;
        win: number;
        lose: number;
        winRate: string;
    }]
}

function RankTable() {
    const [rank, setRank] = useState<userRank | null>(null);
    useEffect(() => {
        const fetchData = async () => {
            try {
                const getAPI = await axios.get(
                    'http://localhost:3000/ranking', {
                    headers: {
                        'Content-Type': 'application/json'
                    }
                });
                setRank(getAPI.data);
            } catch (e) {
                console.log(e);
            }
        };
        fetchData();
    }, []);
    return (
        <div className='rank-table'>
            <RankRow rank='rank' nickName='nickname' win='win' lose='lose' winRate='winRate' type='rank-row-title'></RankRow>
            {rank?.ranking.map((val: any, index: any) => {
                const row_type = index % 2 ? 'rank-row' : 'rank-row-gray';
                return (<RankRow key={index} rank={val.rank} nickName={val.nickName} win={val.win} lose={val.lose} winRate={val.winRate} type={row_type}></RankRow>)
            })}
        </div>
    )
}

function RankRow(props : any) {
    return (
        <div className={props.type}>
            <span className='rank-cell'>{props.rank}</span>
            <span className='rank-cell'>{props.nickName}</span>
            <span className='rank-cell'>{props.win}</span>
            <span className='rank-cell'>{props.lose}</span>
            <span className='rank-cell'>{props.winRate}</span>
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