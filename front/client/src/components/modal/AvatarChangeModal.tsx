import axios from 'axios';
import { useState, useEffect } from 'react';
import { useRecoilValue, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import 'styles/modal/Modal.css';

function AvatarChangeModal() {
  const myData = useRecoilValue(myDataState);
  const [postImg, setPostImg] = useState<FormData>();
  const [isChange, setIsChange] = useState<boolean>();
  const [previewImg, setPreviewImg] = useState(myData.avatar);
  const setModalInfo = useSetRecoilState(modalState);

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  useEffect(() => {
    if (isChange) {
      window.location.reload();
      setIsChange(false);
    }
  }, [isChange]);

  const UploadAvatar = (e: any) => {
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

  const PostAvatar = () => {
    const fetchData = async () => {
      try {
        await axios.patch(
          'http://10.19.236.57:3000/users/' + myData.nickName,
          postImg,
          {
            headers: {
              'Content-Type': 'multipart/form-data',
              Authorization: `Bearer ${localStorage.getItem('tran-token')}`, // 로그인 후 처리
            },
          }
        );
        setIsChange(true);
      } catch (e) {}
    };
    fetchData();
  };

  return (
    <div className='modal'>
      <div className='modalTitle'>avatar change</div>
      <div className='modalContent'>
        <div>
          <input type='file' accept='image/*' onChange={UploadAvatar} />
          <img
            src={previewImg}
            alt='프로필 이미지'
            style={{ width: '100px', height: '100px' }}
          />
          <span>아바타</span>
        </div>
      </div>
      <div className='modalSelect'>
        <button onClick={PostAvatar} className='modalButton'>
          change
        </button>
        <button onClick={CloseModal} className='modalButton'>
          close
        </button>
      </div>
    </div>
  );
}

export default AvatarChangeModal;
