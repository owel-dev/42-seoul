import { useState, useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { loginState } from 'utils/recoil/login';
import { errorState } from 'utils/recoil/error';
import { rankRowType, userRank } from 'types/RankTypes';
import { errorType } from 'types/errorTypes';
import { socket } from 'components/layout/Layout';
import RankRow from 'components/rank/RankRow';
import RankTitleRow from 'components/rank/RankTitleRow';
import instance from 'utils/axios';
import refreshToken from 'utils/token';

function RankTable() {
  const [rank, setRank] = useState<userRank | null>(null);
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const setErrorMessage = useSetRecoilState(errorState);

  const logout = () => {
    socket.emit('logout', () => {
      socket.disconnect();
    });
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
  };

  useEffect(() => {
    getData();
  }, []);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/stat`);
      setRank(getAPI.data);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.status === 403) {
        logout();
      } else if (e.response.data.statusCode === 401) {
        refreshToken()
          .then(() => {
            if (isLoggedIn === true) getData();
          })
          .catch(() => {
            logout();
          });
      } else {
        setErrorMessage('RT01');
      }
    }
  };

  return (
    <div className='rank-table'>
      <RankTitleRow />
      {rank?.ranking.map((val: rankRowType, index: number) => {
        const row_type = index % 2 ? 'rank-row' : 'rank-row-gray';
        return <RankRow key={index} rankrow={val} type={row_type} />;
      })}
    </div>
  );
}

export default RankTable;
