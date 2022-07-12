import { useState, useEffect } from 'react';
import axios from 'axios';
import 'styles/mypage/UserInfo.css';
import { DUMMY_SERVER, DUMMY_USER } from 'utils/dummy';
import { userInfo } from 'types/MyPageTypes';
import Modal from 'components/modal/Modal';
import NickChangeModal from 'components/modal/NickChangeModal';
import AvatarChangeModal from 'components/modal/AvatarChangeModal';
import {
  nickChangeModalState,
  avatarChangeModalState,
} from 'utils/recoil/modalState';
import { useSetRecoilState } from 'recoil';

function UserInfo() {
  const [info, setInfo] = useState<userInfo | null>(null);

  const setNickStatus = useSetRecoilState(nickChangeModalState);
  const openNickModal = () => {
    setNickStatus(true);
  };

  const setAvatarStatus = useSetRecoilState(avatarChangeModalState);
  const openAvatarModal = () => {
    setAvatarStatus(true);
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
        console.log(e);
      }
    };
    fetchData();
  }, []);

  return (
    <div className='user-info'>
      <div id='user-info-left'>
        <img src={info?.avatar} id='avatar' alt='프로필사진'></img>
        <button onClick={openAvatarModal}>change</button>
        <Modal>
          <AvatarChangeModal />
        </Modal>
      </div>
      <div id='user-info-right'>
        <div className='user-info-line'>
          <span className='user-label'>intraID </span>
          <span>{info?.intraId}</span>
        </div>
        <div className='user-info-line'>
          <span className='user-label'>nickname </span>
          <input defaultValue={info?.nickName}></input>
          <button onClick={openNickModal}>change</button>
          <Modal>
            <NickChangeModal />
          </Modal>
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
