import RankTable from 'components/rank/RankTable';
import { useEffect } from 'react';
import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import 'styles/rank/Rank.css';

function Rank() {
  const setModalInfo = useSetRecoilState(modalState);

  useEffect(() => {
    setModalInfo({ modalName: null });
  }, []);

  return (
    <div className='rank'>
      <div id='rank-title'>ranking</div>
      <RankTable />
    </div>
  );
}
export default Rank;
