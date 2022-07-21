import axios from 'axios';
import { useState, useEffect } from 'react';
import { userRank } from 'types/RankTypes';
import { DUMMY_SERVER } from 'utils/dummy';
import RankRow from 'components/rank/RankRow';
import instance from 'utils/axios';

function RankTable() {
  const [rank, setRank] = useState<userRank | null>(null);

  useEffect(() => {
    getData();
  }, []);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/stat`);
      setRank(getAPI.data);
    } catch (e) {}
  };

  return (
    <div className='rank-table'>
      <RankRow
        rank='rank'
        nickName='nickname'
        win='win'
        lose='lose'
        winRate='winRate'
        type='rank-row-title'
      />
      {rank?.ranking.map((val: any, index: any) => {
        const row_type = index % 2 ? 'rank-row' : 'rank-row-gray';
        return (
          <RankRow
            key={index}
            rank={val.rank}
            nickName={val.nickName}
            win={val.win}
            lose={val.lose}
            winRate={val.winRate}
            type={row_type}
          />
        );
      })}
    </div>
  );
}

export default RankTable;
