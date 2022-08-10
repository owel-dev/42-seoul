import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { profileState } from 'utils/recoil/profileData';
import { myDataState } from 'utils/recoil/myData';
import instance from 'utils/axios';
import { errorType } from 'types/errorTypes';
import { errorState } from 'utils/recoil/error';
import 'styles/users/UserInfo.css';

function UserInfo() {
  const myData = useRecoilValue(myDataState);
  const [profileData, setProfileData] = useRecoilState(profileState);
  const setModalInfo = useSetRecoilState(modalState);
  const setErrorMessage = useSetRecoilState(errorState);

  const openNickModal = () => {
    setModalInfo({ modalName: 'USER-NICK' });
  };

  const openAvatarModal = () => {
    setModalInfo({ modalName: 'USER-AVATAR' });
  };

  const addFriend = async () => {
    try {
      await instance.post(`/friend`, {
        player1: myData.nickName,
        player2: profileData.nickName,
      });
      alert('친구 추가가 완료되었습니다.');
      setProfileData((prev) => ({ ...prev, isFriend: true }));
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
      await instance.delete(`/friend?nickname=${profileData.nickName}`);
      alert('친구 삭제가 완료되었습니다.');
      setProfileData((prev) => ({ ...prev, isFriend: false }));
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

  return (
    <div className='user-info'>
      <div id='user-info-left'>
        <img src={profileData?.avatar} id='user-avatar' alt='프로필사진'></img>
        <div>
          {myData.nickName === profileData.nickName ? (
            <button onClick={openAvatarModal} className='changeButton'>
              change
            </button>
          ) : null}
        </div>
      </div>
      <div id='user-info-right'>
        <div className='user-info-line'>
          <span className='user-label'>intraID </span>
          <span>{profileData?.intraId}</span>
        </div>
        <div className='user-info-line'>
          <span className='user-label'>nickname </span>
          <span> {profileData?.nickName}</span>
          {myData.nickName === profileData.nickName ? (
            <button onClick={openNickModal} className='changeButton'>
              change
            </button>
          ) : null}
        </div>
        <div className='user-info-line'>
          <span>{profileData.win} </span>
          <span>win </span>
          <span>{profileData.lose} </span>
          <span>lose </span>
          <span>winRate : </span>
          <span>{profileData.winRate} </span>
          {profileData?.nickName !== myData.nickName ? (
            <div>
              {profileData?.isFriend === false ? (
                <button className='changeButton' onClick={addFriend}>
                  친구 추가
                </button>
              ) : (
                <button className='changeButton' onClick={delFriend}>
                  친구 제거
                </button>
              )}
            </div>
          ) : (
            <></>
          )}
        </div>
      </div>
    </div>
  );
}

export default UserInfo;
