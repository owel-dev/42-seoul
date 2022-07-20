function GameMatchWait(props: any) {
  return (
    <div className='modal'>
      <div className='modal-title'>game start</div>
      <div className='modal-content'>
        <div>대기중입니다..</div>
      </div>
      <div className='modal-select'>
        <button onClick={props.matchRequest}>regist</button>
        <button onClick={props.CloseModal}>close</button>
      </div>
    </div>
  );
}
export default GameMatchWait;
