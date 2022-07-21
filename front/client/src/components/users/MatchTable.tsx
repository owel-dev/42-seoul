import { useState, useEffect } from 'react';
import { useRecoilValue } from 'recoil';
import { matchList } from 'types/profileTypes';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import { profileState } from 'utils/recoil/profileData';
import instance from 'utils/axios';
import 'styles/users/MatchTable.css';

function MatchTable() {
  const profileData = useRecoilValue(profileState);
  const [matchList, setMatchList] = useState<matchList | null>(null);

  useEffect(() => {
    getData();
  }, []);

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/match/` + profileData.nickName); // 로그인 후 처리
      setMatchList(getAPI.data);
    } catch (e) {}
  };

  return (
    <div className='match-table'>
      {matchList?.matchList.map((element, index) => {
        return (
          <div className='match-row' key={index}>
            <a href={`/users/${element.player1}`}>
              <span>{element.player1}</span>
            </a>
            <span> {element.score1}</span>
            <span> vs </span>
            <a href={`/users/${element.player2}`}>
              <span>{element.player2}</span>
            </a>
            <span> {element.score2}</span>
          </div>
        );
      })}
    </div>
  );
}
export default MatchTable;
