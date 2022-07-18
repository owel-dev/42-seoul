import axios from 'axios';
import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { matchList } from 'types/profileTypes';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import 'styles/users/MatchTable.css';

function MatchTable() {
  const [List, setList] = useState<matchList | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(
          DUMMY_SERVER + '/match/' + DUMMY_USER.intraId,
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
        setList(getAPI.data);
      } catch (e) {}
    };
    fetchData();
  }, []);

  return (
    <div className='match-table'>
      {List?.matchList.map((element, index) => {
        return (
          <div className='match-row' key={index}>
            <Link to={`/users/yongwkim`}>
              <span>{element.player1}</span>
            </Link>
            <span> {element.score1}</span>
            <span> vs </span>
            <Link to={`/users/yongwkim`}>
              <span>{element.player2}</span>
            </Link>
            <span> {element.score2}</span>
          </div>
        );
      })}
    </div>
  );
}
export default MatchTable;
