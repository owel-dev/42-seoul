import { Link } from 'react-router-dom';

function RankRow(props: any) {
  return (
    <div className={props.type}>
      <span className='rank-cell'>{props.rank}</span>
      <Link className='rank-cell' to={`/users/${props.nickName}/mypage`}>
        <span>{props.nickName}</span>
      </Link>
      <span className='rank-cell'>{props.win}</span>
      <span className='rank-cell'>{props.lose}</span>
      <span className='rank-cell'>{props.winRate}</span>
    </div>
  );
}

export default RankRow;
