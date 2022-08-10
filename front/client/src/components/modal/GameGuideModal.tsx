import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import 'styles/modal/LogoutModal.css';

function GameGuideModal() {
  const setModalInfo = useSetRecoilState(modalState);

  const onReturn = () => {
    setModalInfo({ modalName: null });
  };

  return (
    <div className='modal'>
      <div className='modalTitle'>게임설명</div>
      <div className='modalContent'>
        <div>
          게임 방법 : 마우스를 움직여 패들을 조작할 수 있습니다.
          <br />
          패들을 이용해 공을 튕겨내 상대방이 받아치지 못하면 점수를 얻습니다.
          <br />
          먼저 10점을 달성하는 사람이 승리합니다.
        </div>
      </div>
      <div className='modalSelect'>
        <span>
          <input
            onClick={onReturn}
            type='button'
            value='닫기'
            className='modalButton'
          />
        </span>
      </div>
    </div>
  );
}

export default GameGuideModal;
