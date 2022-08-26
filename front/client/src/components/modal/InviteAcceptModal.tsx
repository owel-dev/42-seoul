import { useEffect } from 'react';
import { Navigate } from 'react-router-dom';
import { useRecoilState, useRecoilValue, useSetRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { inviteType } from 'types/GameTypes';
import { modalState } from 'utils/recoil/modal';
import { channelState, inviteState, matchState } from 'utils/recoil/gameState';
import 'styles/modal/Modal.css';

function InviteAcceptModal() {
  const inviteData = useRecoilValue<inviteType>(inviteState);
  const setModalState = useSetRecoilState(modalState);
  const [channelInfo, setChannelInfo] = useRecoilState(channelState);
  const setMatchWait = useSetRecoilState(matchState);

  const inviteAccept = () => {
    socket.emit('together-response', { status: true, data: inviteData });
  };
  const inviteDeny = () => {
    socket.emit('together-response', { status: false, data: inviteData });
    setModalState({ modalName: null });
  };

  useEffect(() => {
    setChannelInfo({channelId: '', firstPlayer: '', secondPlayer: ''});
    let checkalert = false;
    socket.on('game-wait', (data) => {
      setChannelInfo(data);
    });
    socket.on('match-cancel', () => {
      setMatchWait(false);
      if (checkalert === false) {
        alert(`${inviteData.nickName}(이)가 같이하기를 취소하였습니다.`);
        checkalert = true;
      }
      setModalState({ modalName: null });
    });
  }, []);

  return (
    <>
      {channelInfo.channelId ? (
        <Navigate to={'/channel/' + channelInfo.channelId} />
      ) : (
        <div className='modal'>
          <div className='modalTitle'>Invite Accept</div>
          <div className='modalContent'>
            {inviteData.nickName}님의 초대를 수락하겠습니까?
          </div>
          <div className='modalSelect'>
            <button className='modalButton' onClick={inviteAccept}>
              수락
            </button>
            <button className='modalButton' onClick={inviteDeny}>
              거절
            </button>
          </div>
        </div>
      )}
    </>
  );
}
export default InviteAcceptModal;
