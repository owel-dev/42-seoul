import axios from 'axios';
import React, {useState, useEffect} from 'react';
import './Rank.css'

type user = {
    nickName: string;
    win: number;
    lose: number;
    winRate: number;
}

function RankTable({props}: {props : user[]}) {
    props.forEach((element : any, index : number) => {
        element.rank = index + 1;
    });
    return (
        <div className='rank-table'>
            <RankRow rank='rank' nickName='nickname' win='win' lose='lose' winRate='winRate' type='rank-row-title'></RankRow>
            {props.map((val: any, index: any) => {
                let row_type : string;
                if (index % 2 === 1)
                    row_type = 'rank-row-gray';
                else
                    row_type = 'rank-row';
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
    const [rank, setRank] = useState(null);
    const [loading, setLoading] = useState(false);
    useEffect(() => {
        const fetchData = async () => {
            setLoading(true);
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
            setLoading(false);
        };
        fetchData();
    }, []);

    if (loading) {
        return (<div>로딩중</div>);
    }
    if (rank == null)
    {
        return (<div>실패🥲</div>);
    }
    const rankObj = Object.entries(rank);//오브젝트로 변환
    const userArr :  user[] = [];//user 타입으로 담을 arr 선언
    rankObj.forEach((element) => {//arr에 오브젝트의 요소들을 하나씩 user타입으로 변환해 넣어준다
        const userize : user = element[1] as user;
        userArr.push(userize);
    });
    return (
        <div className='rank'>
            <h1>ranking</h1>
            <RankTable props={userArr}></RankTable>
        </div>
    )
}
export default Rank;