import MatchTable from 'components/users/MatchTable';
import 'styles/users/MatchList.css';

function MatchList() {
  return (
    <div className='matchList'>
      <div className='matchTitle'>Match history</div>
      <MatchTable />
    </div>
  );
}

export default MatchList;
