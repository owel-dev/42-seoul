import axios from 'axios';
import { useState, useEffect } from 'react';
import { useRecoilState, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { errorState } from 'utils/recoil/error';
import { profileState } from 'utils/recoil/profileData';
import { errorType } from 'types/errorTypes';
import 'styles/modal/Modal.css';

function AvatarChangeModal() {
  const [myData, setMyData] = useRecoilState(myDataState);
  const setProfileData = useSetRecoilState(profileState);
  const setModalInfo = useSetRecoilState(modalState);
  const setErrorMessage = useSetRecoilState(errorState);
  const [postImg, setPostImg] = useState<FormData>();
  const [isChange, setIsChange] = useState<boolean>();
  const [previewImg, setPreviewImg] = useState(myData.avatar);

  const closeModal = () => {
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    if (isChange) {
      setModalInfo({ modalName: null });
      setIsChange(false);
    }
  }, [isChange]);

  const uploadAvatar = (e: React.ChangeEvent<HTMLInputElement>) => {
    if (!e.target.files) return;

    const rd = new FileReader();
    const file: Blob = e.target.files[0];
    //미리보기
    rd.readAsDataURL(file);
    setPreviewImg(URL.createObjectURL(file));
    //전송할 FormData
    const img = new FormData();
    img.append('avatar', file);
    setPostImg(img);
  };

  const postAvatar = async () => {
    try {
      const res = await axios.patch(
        `${process.env.REACT_APP_SERVERIP}/users/` + myData.nickName,
        postImg,
        {
          headers: {
            'Content-Type': 'multipart/form-data',
            Authorization: `Bearer ${localStorage.getItem('accessToken')}`,
          },
        }
      );
      setMyData((prev) => ({ ...prev, avatar: res.data }));
      setProfileData((prev) => ({ ...prev, avatar: res.data }));
      setIsChange(true);
    } catch (err) {
      const e = err as errorType;
      if (e.message === `Network Error`) {
        setErrorMessage('E500');
      } else if (e.response.data.statusCode === 'AC01')
        alert('jpg, jpeg, png, gif 파일만 등록 가능합니다.');
      else if (e.response.data.statusCode === 'AC02')
        alert('10MB 이하의 파일만 등록 가능합니다.');
      else setErrorMessage('AM01');
    }
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
