import RankTable from 'components/rank/RankTable';
import 'styles/rank/Rank.css';

function Rank() {
  return (
    <div className='rank'>
      <div id='rank-title'>ranking</div>
      <RankTable />
    </div>
  );
}
export default Rank;
