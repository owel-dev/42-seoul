import { Link } from 'react-router-dom';
import { rankRowType } from 'types/RankTypes';

function RankRow(props: { key: number; rankrow: rankRowType; type: string }) {
  return (
    <div className={props.type}>
      <span className='rank-cell'>{props.rankrow.rank}</span>
      <Link
        className='rank-cell'
        to={`/users/${props.rankrow.nickName}/mypage`}
      >
        <span>{props.rankrow.nickName}</span>
      </Link>
      <span className='rank-cell'>{props.rankrow.win}</span>
      <span className='rank-cell'>{props.rankrow.lose}</span>
      <span className='rank-cell'>{props.rankrow.winRate}</span>
    </div>
  );
}

export default RankRow;
