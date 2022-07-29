import axios from 'axios';
import { useState, useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { errorState } from 'utils/recoil/error';
import { profileState } from 'utils/recoil/profileData';
import 'styles/modal/Modal.css';

function AvatarChangeModal() {
  const [myData, setMyData] = useRecoilState(myDataState);
  const [profileData, setProfileData] = useRecoilState(profileState);
  const [postImg, setPostImg] = useState<FormData>();
  const [isChange, setIsChange] = useState<boolean>();
  const [previewImg, setPreviewImg] = useState(myData.avatar);
  const setModalInfo = useSetRecoilState(modalState);
  const setErrorMessage = useSetRecoilState(errorState);

  const closeModal = () => {
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    if (isChange) {
      setModalInfo({ modalName: null });
      setIsChange(false);
    }
  }, [isChange]);

  const uploadAvatar = (e: any) => {
    const rd = new FileReader();

    if (e.target.files[0] !== null) {
      //미리보기
      rd.readAsDataURL(e.target.files[0]);
      setPreviewImg(URL.createObjectURL(e.target.files[0]));

      //전송할 FormData
      const img = new FormData();
      img.append('avatar', e.target.files[0]);
      setPostImg(img);
    }
  };

  const postAvatar = () => {
    const fetchData = async () => {
      try {
        const res = await axios.patch(
          `${process.env.REACT_APP_SERVERIP}/users/` + myData.nickName,

          postImg,
          {
            headers: {
              'Content-Type': 'multipart/form-data',
              Authorization: `Bearer ${localStorage.getItem('trans-token')}`, // 로그인 후 처리
            },
          }
        );
        setIsChange(true);
        setMyData({
          nickName: myData.nickName,
          avatar: res.data,
          admin: myData.admin,
          isSecondAuth: myData.isSecondAuth,
        });
        setProfileData({
          intraId: profileData.intraId,
          avatar: res.data,
          nickName: profileData.nickName,
          win: profileData.win,
          lose: profileData.lose,
          winRate: profileData.winRate,
        });
      } catch (e: any) {
        if (e.message === `Network Error`) {
          setErrorMessage('E500');
        } else if (e.response.data.statusCode === 'AC01')
          alert('jpg, jpeg, png, gif 파일만 등록 가능합니다.');
        else if (e.response.data.statusCode === 'AC02')
          alert('10MB 이하의 파일만 등록 가능합니다.');
        else setErrorMessage('AM01');
      }
    };
    fetchData();
  };

  return (
    <div className='modal'>
      <div className='modalTitle'>avatar change</div>
      <div className='modalContent'>
        <div>
          <input
            type='file'
            accept='.jpg, .jpeg, .png, .gif'
            onChange={uploadAvatar}
          />
          <img
            src={previewImg}
            alt='프로필 이미지'
            style={{ width: '100px', height: '100px' }}
          />
        </div>
      </div>
      <div className='modalSelect'>
        <button onClick={postAvatar} className='modalButton'>
          change
        </button>
        <button onClick={closeModal} className='modalButton'>
          close
        </button>
      </div>
    </div>
  );
}

export default AvatarChangeModal;
