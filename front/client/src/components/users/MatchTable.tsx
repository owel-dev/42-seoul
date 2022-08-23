import { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { matchList } from 'types/profileTypes';
import { errorType } from 'types/errorTypes';
import { profileState } from 'utils/recoil/profileData';
import { errorState } from 'utils/recoil/error';
import { loginState } from 'utils/recoil/login';
import instance from 'utils/axios';
import refreshToken from 'utils/token';
import 'styles/users/MatchList.css';

function MatchTable() {
  const profileData = useRecoilValue(profileState);
  const [matchList, setMatchList] = useState<matchList | null>(null);
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

  const getData = async () => {
    try {
      const getAPI = await instance.get(`/match/` + profileData.nickName);
      setMatchList(getAPI.data);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 401) {
        refreshToken()
          .then(() => {
            if (isLoggedIn === true) getData();
          })
          .catch(() => {
            logout();
          });
      } else setErrorMessage('MT01');
    }
  };

  useEffect(() => {
    getData();
  }, []);

  return (
    <div className='matchTable'>
      {matchList !== null ? (
        <>
          {matchList?.matchList.map((element, index) => (
            <div className='matchRow' key={index}>
              <span className='matchLeft'>
                <Link to={`/users/${element.player1}/mypage`}>
                  <span
                    onClick={() => {
                      socket.emit('friend-end');
                    }}
                  >
                    {element.player1}
                  </span>
                </Link>
                <span> {element.score1}</span>
              </span>
              <span className='matchMiddle'> vs </span>
              <span className='matchRight'>
                <Link to={`/users/${element.player2}/mypage`}>
                  <span
                    onClick={() => {
                      socket.emit('friend-end');
                    }}
                  >
                    {element.player2}
                  </span>
                </Link>
                <span> {element.score2}</span>
              </span>
            </div>
          ))}
        </>
      ) : (
        <></>
      )}
    </div>
  );
}
export default MatchTable;
