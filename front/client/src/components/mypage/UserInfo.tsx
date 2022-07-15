import axios from 'axios';
import { useState, useEffect } from 'react';
import { useSetRecoilState } from 'recoil';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import { userInfo } from 'types/MyPageTypes';
import { modalState } from 'types/modal';
import 'styles/mypage/UserInfo.css';

function UserInfo() {
  const [info, setInfo] = useState<userInfo | null>(null);
  const setModalInfo = useSetRecoilState(modalState);

  const openNickModal = () => {
    setModalInfo({ modalName: 'USER-NICK' });
  };

  const openAvatarModal = () => {
    setModalInfo({ modalName: 'USER-AVATAR' });
  };

  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(
          DUMMY_SERVER + 'users/' + DUMMY_USER.intraId + '/mypage',
          {
            headers: {
              'Content-Type': 'application/json',
            },
          }
        );
        setInfo(getAPI.data);
      } catch (e) {
        // console.log(e);
      }
    };
    fetchData();
  }, []);

  return (
    <div className='user-info'>
      <div id='user-info-left'>
        <img src={info?.avatar} id='avatar' alt='프로필사진'></img>
        <button onClick={openAvatarModal}>change</button>
      </div>
      <div id='user-info-right'>
        <div className='user-info-line'>
          <span className='user-label'>intraID </span>
          <span>{info?.intraId}</span>
        </div>
        <div className='user-info-line'>
          <span className='user-label'>nickname </span>
          <span> {info?.nickName}</span>
          <button onClick={openNickModal}>change</button>
        </div>
        <div className='user-info-line'>
          <span>{info?.win} </span>
          <span>win </span>
          <span>{info?.lose} </span>
          <span>lose </span>
          <span>winRate : </span>
          <span>{info?.winRate} </span>
        </div>
      </div>
    </div>
  );
}

export default UserInfo;
