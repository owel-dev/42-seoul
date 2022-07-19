import MatchTable from 'components/users/MatchTable';
import 'styles/users/MatchList.css';

function MatchList() {
  return (
    <div className='match-list'>
      <h3>Match history</h3>
      <MatchTable />
    </div>
  );
}

export default MatchList;
