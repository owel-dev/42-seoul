//할 일 : 이 모달에 대한 Status 추가하고,,,
//layout에서 socket.on('특정이벤트') 되면 이 모달을 켜고
//여기서는 누구의 초대를 수락하겠습니까? 예 아니오
import 'styles/modal/Modal.css';

function InviteAcceptModal() {
  //const 수락하기 = () => {socket.emit('수락이벤트')};
  //const 거절하기 = () => {socket.emit('거절이벤트')};

  //socket.on('game-wait') 후 Navigate하기 GameStartModal과 비슷함
  /*
    const [channelInfo, setChannelInfo] = useRecoilState(channelState);

    useEffect(() => {
        socket.on('game-wait', (data) => {
        setChannelInfo(data);
        });
    }, [setChannelInfo]);
  */
  return (
    <div className='modal'>
      <div className='modalTitle'>Invite Accept</div>
      <div className='modalContent'>~~님의 초대를 수락하시겟습끼나?</div>
      <div className='modalSelect'>
        <button className='modalButton'>수락</button>
        <button className='modalButton'>거절</button>
      </div>
    </div>
  );
}
export default InviteAcceptModal;
