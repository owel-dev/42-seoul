import { useState, useEffect } from 'react';
import axios from 'axios';
import 'styles/mypage/MatchTable.css';
import { matchList } from 'types/MyPageTypes';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';

function MatchTable() {
  const [List, setList] = useState<matchList | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(
          DUMMY_SERVER + 'match/' + DUMMY_USER.intraId,
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
        setList(getAPI.data);
      } catch (e) {
        console.log(e);
      }
    };
    fetchData();
  }, []);

  return (
    <div className='match-table'>
      {List?.matchList.map((element, index) => {
        return (
          <div className='match-row' key={index}>
            <span>{element.player1} </span>
            <span>{element.score1}</span>
            <span> vs </span>
            <span>{element.player2} </span>
            <span>{element.score2}</span>
          </div>
        );
      })}
    </div>
  );
}
export default MatchTable;
