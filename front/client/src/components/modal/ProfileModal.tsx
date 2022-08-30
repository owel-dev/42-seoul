import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { userData } from 'types/userTypes';
import { errorType } from 'types/errorTypes';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { chatListState, messageState } from 'utils/recoil/chat';
import { channelState } from 'utils/recoil/gameState';
import { friendState } from 'utils/recoil/friend';
import { errorState } from 'utils/recoil/error';
import { loginState } from 'utils/recoil/login';
import instance from 'utils/axios';
import refreshToken from 'utils/token';
import 'styles/modal/Modal.css';

function ProfileModal() {
  const myData = useRecoilValue(myDataState);
  const [userData, setUserData] = useState<userData>();
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [friend, setFriend] = useRecoilState(friendState);
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const setMessage = useSetRecoilState(messageState);
  const setErrorMessage = useSetRecoilState(errorState);
  const setChatList = useSetRecoilState(chatListState);

  const logout = () => {
    socket.emit('logout', () => {
      socket.disconnect();
    });
    localStorage.removeItem('accessToken');
    localStorage.removeItem('refreshToken');
    setIsLoggedIn(false);
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    getUserData();
  }, []);

  const getUserData = async () => {
    try {
      const res = await instance.get(`/users/${modalInfo.user}/modal`);
      setUserData(res?.data);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'PU01') {
        alert('존재하지 않는 사용자입니다.');
        setModalInfo({ modalName: null });
      } else if (e.response.data.statusCode === 401) {
        refreshToken()
          .then(() => {
            if (isLoggedIn === true) getUserData();
          })
          .catch(() => {
            logout();
          });
      } else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM01');
      }
    }
  };

  const moveProfile = () => {
    if (channelInfo.channelId !== '') {
      setChannelInfo({
        channelId: '',
        firstPlayer: '',
        secondPlayer: '',
      });
      setChatList([]);
      socket.emit('leave-channel');
    }
    if (friend) {
      setFriend(false);
      socket.emit('friend-end');
    }
    setModalInfo({ modalName: null });
  };

  const addFriend = async () => {
    try {
      await instance.post(`/friend`, {
        player1: myData.nickName,
        player2: modalInfo.user,
      });
      alert('친구 추가가 완료되었습니다.');
      setModalInfo({ modalName: null });
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'FA01')
        alert('이미 등록된 상태입니다.');
      else if (e.response.data.statusCode === 'FA02')
        alert('존재하지 않는 사용자입니다.');
      else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM02');
      }
      setModalInfo({ modalName: null });
    }
  };

  const delFriend = async () => {
    try {
      await instance.delete(`/friend?nickname=${modalInfo.user}`);
      alert('친구 삭제가 완료되었습니다.');
      setModalInfo({ modalName: null });
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'FD01')
        alert('친구 목록에 없는 유저입니다.');
      else if (e.response.data.statusCode === 'FD02')
        alert('존재하지 않는 사용자입니다.');
      else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM03');
      }
      setModalInfo({ modalName: null });
    }
  };

  const banUser = async () => {
    try {
      await instance.post(`/ban`, {
        player1: myData.nickName,
        player2: modalInfo.user,
      });
      alert('차단이 완료되었습니다.');
      setModalInfo({ modalName: null });
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'BA01')
        alert('이미 차단된 상태입니다.');
      else if (e.response.data.statusCode === 'BA02')
        alert('존재하지 않는 사용자입니다.');
      else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM04');
      }
      setModalInfo({ modalName: null });
    }
  };

  const banCancel = async () => {
    try {
      await instance.delete(`/ban?user=${modalInfo.user}`);
      alert('차단이 해제되었습니다.');
      setModalInfo({ modalName: null });
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'BD01')
        alert('차단되지 않은 사용자입니다.');
      else if (e.response.data.statusCode === 'BD02')
        alert('존재하지 않는 사용자입니다.');
      else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM05');
      }
      setModalInfo({ modalName: null });
    }
  };

  const mute = () => {
    socket.emit('mute', userData?.nickName);
    alert(`${userData?.nickName}이 30초간 음소거 되었습니다.`);
    setModalInfo({ modalName: null });
  };

  const setAdmin = () => {
    if (userData?.admin) {
      socket.emit('cancel-admin', userData?.nickName);
    } else {
      socket.emit('set-admin', userData?.nickName);
    }
    setModalInfo({ modalName: null });
  };

  const sendDM = () => {
    setMessage(`#${userData?.nickName} `);
    setModalInfo({ modalName: null });
  };

  const sendInvite = () => {
    setModalInfo({ modalName: 'GAME-INVITE', user: modalInfo.user });
  };

  return (
    <>
      {userData?.nickName && (
        <div className='modal'>
          <div className='modalTitle'>유저 프로필</div>
          <div className='modalContent'>
            <section>
              <span>{modalInfo.user}</span>
              <Link to={`/users/${modalInfo.user}/mypage`}>
                <input
                  type='button'
                  onClick={moveProfile}
                  value='프로필'
                  className='modalButtonInner'
                />
              </Link>
              <br />
              <span>{`${userData.win} 승`} </span>
              <span>{`${userData.lose} 패`} </span>
              <span>{`승률 ${userData.winRate}`}</span>
            </section>
            <br />
            <>
              {userData.nickName !== myData.nickName && (
                <section>
                  {userData.status === 'online' && channelInfo.channelId === '' && (
                    <input
                      type='button'
                      onClick={sendInvite}
                      value='같이하기'
                      className='modalButtonInner'
                    />
                  )}
                  <input
                    type='button'
                    onClick={sendDM}
                    value='귓말하기'
                    className='modalButtonInner'
                  />
                  <input
                    type='button'
                    className='modalButtonInner'
                    onClick={userData.friend ? delFriend : addFriend}
                    value={userData.friend ? '친구삭제' : '친구추가'}
                  />
                  <input
                    type='button'
                    className='modalButtonInner'
                    onClick={userData.ban ? banCancel : banUser}
                    value={userData.ban ? '차단해제' : '차단하기'}
                  />
                  {(myData.owner || myData.admin) && (
                    <>
                      {!userData.owner && (
                        <input
                          type='button'
                          onClick={mute}
                          value='음소거'
                          className='modalButtonInner'
                        />
                      )}
                      {myData.owner && (
                        <input
                          type='button'
                          onClick={setAdmin}
                          value={userData.admin ? '방장박탈' : '방장임명'}
                          className='modalButtonInner'
                        />
                      )}
                    </>
                  )}
                </section>
              )}
            </>
          </div>
          <div className='modalSelect'>
            <button
              onClick={() => {
                setModalInfo({ modalName: null });
              }}
              className='modalButton'
            >
              닫기
            </button>
          </div>
        </div>
      )}
    </>
  );
}
export default ProfileModal;
