import MatchTable from 'components/mypage/MatchTable';
import 'styles/mypage/MatchList.css';

function MatchList() {
  return (
    <div className='match-list'>
      <h3>Match history</h3>
      <MatchTable />
    </div>
  );
}

export default MatchList;
