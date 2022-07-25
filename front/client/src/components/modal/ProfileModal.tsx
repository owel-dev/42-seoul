import { Link } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { userData } from 'types/userTypes';
import { myDataState } from 'utils/recoil/myData';
import { messageState } from 'utils/recoil/chat';
import instance from 'utils/axios';
import 'styles/modal/Modal.css';
import { socket } from 'components/layout/Layout';

function ProfileModal() {
  const myData = useRecoilValue(myDataState);
  const [userData, setUserData] = useState<userData>();
  const [modalInfo, setModalInfo] = useRecoilState(modalState);
  const setMessage = useSetRecoilState(messageState);

  useEffect(() => {
    getUserData();
  }, []);

  const getUserData = async () => {
    try {
      const res = await instance.get(`/users/${modalInfo.user}/modal`);
      setUserData(res?.data);
    } catch (e) {}
  };

  const moveProfile = () => {
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
      if (e.response.data.statusCode === 400) alert('이미 등록된 상태입니다.');
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
      if (e.response.data.statusCode === 400)
        alert('친구 목록에 없는 유저입니다.');
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
      if (e.response.data.statusCode === 400) alert('이미 차단된 상태입니다.');
    }
  };

  const banCancel = async () => {
    try {
      await instance.delete(`/ban?user=${modalInfo.user}`);
      alert('차단이 해제되었습니다.');
      setModalInfo({ modalName: null });
    } catch (e: any) {
      if (e.response.data.statusCode === 400)
        alert('차단되지 않은 사용자입니다.');
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

  return (
    <>
      {userData?.nickName && (
        <div className='modal'>
          <div className='modalTitle'>유저 프로필</div>
          <div className='modalContent'>
            <section>
              <span>{modalInfo.user}</span>
              <Link to={`/users/${modalInfo.user}/mypage`}>
                <input type='button' onClick={moveProfile} value='프로필' />
              </Link>
              <br />
              <span>{`${userData.win} 승`} </span>
              <span>{`${userData.lose} 패`} </span>
              <span>{`승률 ${userData.win}%`}</span>
            </section>
            <>
              {userData.nickName !== myData.nickName && (
                <section>
                  <button>같이하기</button>
                  <input type='button' onClick={sendDM} value='DM보내기' />
                  <input
                    type='button'
                    onClick={userData.friend ? delFriend : addFriend}
                    value={userData.friend ? '친구삭제' : '친구추가'}
                  />
                  <input
                    type='button'
                    onClick={userData.ban ? banCancel : banUser}
                    value={userData.ban ? '차단해제' : '차단하기'}
                  />
                  {myData.admin && (
                    <>
                      <input type='button' onClick={mute} value='음소거' />
                      <input
                        type='button'
                        onClick={setAdmin}
                        value='방장위임'
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
