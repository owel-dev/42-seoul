import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { userData } from 'types/userTypes';
import { myDataState } from 'utils/recoil/myData';
import { messageState } from 'utils/recoil/chat';
import { socket } from 'components/layout/Layout';
import { channelState } from 'utils/recoil/gameState';
import { friendState } from 'utils/recoil/friend';
import { errorState } from 'utils/recoil/error';
import instance from 'utils/axios';
import 'styles/modal/Modal.css';

function ProfileModal() {
  const myData = useRecoilValue(myDataState);
  const [userData, setUserData] = useState<userData>();
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const [friend, setFriend] = useRecoilState(friendState);
  const setMessage = useSetRecoilState(messageState);
  const setErrorMessage = useSetRecoilState(errorState);

  useEffect(() => {
    getUserData();
  }, []);

  const getUserData = async () => {
    try {
      const res = await instance.get(`/users/${modalInfo.user}/modal`);
      setUserData(res?.data);
    } catch (e: any) {
      if (e.response.data.statusCode === 'PU01') {
        alert('존재하지 않는 사용자입니다.');
        setModalInfo({ modalName: null });
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
    } catch (e: any) {
      if (e.response.data.statusCode === 'FA01')
        alert('이미 등록된 상태입니다.');
      else if (e.response.data.statusCode === 'FA02')
        alert('존재하지 않는 사용자입니다.');
      else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM02');
      }
      setModalInfo({ modalName: null });
    }
    if (window.location.pathname === `/users/${myData.nickName}/mypage`)
      window.location.reload();
  };

  const delFriend = async () => {
    try {
      await instance.delete(`/friend?nickname=${modalInfo.user}`);
      alert('친구 삭제가 완료되었습니다.');
      setModalInfo({ modalName: null });
    } catch (e: any) {
      if (e.response.data.statusCode === 'FD01')
        alert('친구 목록에 없는 유저입니다.');
      else if (e.response.data.statusCode === 'FD02')
        alert('존재하지 않는 사용자입니다.');
      else {
        setModalInfo({ modalName: null });
        setErrorMessage('PM03');
      }
      setModalInfo({ modalName: null });
    }
    if (window.location.pathname === `/users/${myData.nickName}/mypage`)
      window.location.reload();
  };

  const banUser = async () => {
    try {
      await instance.post(`/ban`, {
        player1: myData.nickName,
        player2: modalInfo.user,
      });
      alert('차단이 완료되었습니다.');
      setModalInfo({ modalName: null });
    } catch (e: any) {
      if (e.response.data.statusCode === 'BA01')
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
    } catch (e: any) {
      if (e.response.data.statusCode === 'BD01')
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
    socket.emit('admin', userData?.nickName);
    alert(`${userData?.nickName}에게 방장을 위임하였습니다.`);
    setModalInfo({ modalName: null });
  };

  const sendDM = () => {
    setMessage(`#${userData?.nickName} `);
    setModalInfo({ modalName: null });
  };

  const sendInvite = () => {
    //지금 모달 대신 초대하기 모달로 State 바꿔주기
    //setModalInfo({ modalName: 초대하기모달 });
    //초대하기 모달에서 방 설정, 비밀번호 설정 다 해서 보내기
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
              <span>{`승률 ${userData.win}%`}</span>
            </section>
            <br />
            <>
              {userData.nickName !== myData.nickName && (
                <section>
                  <input
                    type='button'
                    onClick={sendInvite}
                    value='같이하기'
                    className='modalButtonInner'
                  />
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
                  {myData.admin && (
                    <>
                      <input
                        type='button'
                        onClick={mute}
                        value='음소거'
                        className='modalButtonInner'
                      />
                      <input
                        type='button'
                        onClick={setAdmin}
                        value='방장위임'
                        className='modalButtonInner'
                      />
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
