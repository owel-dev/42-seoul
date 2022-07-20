function GameOption(props: any) {
  // return <div></div>;
  return (
    <div className='modal'>
      <div className='modal-title'>game start</div>
      <div className='modal-content'>
        <fieldset>
          <legend>game option</legend>
          <div>
            <input
              type='radio'
              name='drone'
              id='none'
              value='none'
              onChange={() => props.radioChange('none')}
            ></input>
            <label>none</label>
          </div>
          <div>
            <input
              type='radio'
              name='drone'
              id='map'
              value='map'
              onChange={() => props.radioChange('map')}
            ></input>
            <label>map option</label>
          </div>
          <div>
            <input
              type='radio'
              name='drone'
              id='power'
              value='power'
              onChange={() => props.radioChange('power')}
            ></input>
            <label>power option</label>
          </div>
        </fieldset>
        <div>
          <span>비밀번호 </span>
          <input
            placeholder={'비밀번호 입력'}
            onChange={(e) => props.setInputValue(e.target.value)}
          />
        </div>
      </div>
      <div className='modal-select'>
        <button onClick={props.matchRequest}>regist</button>
        <button onClick={props.CloseModal}>close</button>
      </div>
    </div>
  );
}

export default GameOption;
