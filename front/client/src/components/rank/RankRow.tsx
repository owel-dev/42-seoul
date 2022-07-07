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

export default RankRow;