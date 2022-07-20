import axios from 'axios';
import { useState, useEffect } from 'react';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import { profileType } from 'types/profileTypes';
import { modalState } from 'utils/recoil/modal';
import { profileState } from 'utils/recoil/profileData';
import { myDataState } from 'utils/recoil/myData';
import instance from 'utils/axios';
import 'styles/users/UserInfo.css';

function UserInfo() {
  const myData = useRecoilValue(myDataState);
  const [profileData, setProfileData] = useRecoilState(profileState);
  const setModalInfo = useSetRecoilState(modalState);

  const openNickModal = () => {
    setModalInfo({ modalName: 'USER-NICK' });
  };

  const openAvatarModal = () => {
    setModalInfo({ modalName: 'USER-AVATAR' });
  };

  return (
    <div className='user-info'>
      <div id='user-info-left'>
        <img src={profileData?.avatar} id='avatar' alt='프로필사진'></img>
        {myData.nickName === profileData.nickName ? (
          <button onClick={openAvatarModal}>change</button>
        ) : null}
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
            <button onClick={openNickModal}>change</button>
          ) : null}
        </div>
        <div className='user-info-line'>
          <span>{profileData.win} </span>
          <span>win </span>
          <span>{profileData.lose} </span>
          <span>lose </span>
          <span>winRate : </span>
          <span>{profileData.winRate} </span>
        </div>
      </div>
    </div>
  );
}

export default UserInfo;
