import { gameStartModalState } from 'utils/recoil/modalState';
import { useRecoilState } from 'recoil';
import 'styles/modal/Modal.css';

function GameStartModal() {
  const [status, setStatus] = useRecoilState(gameStartModalState);
  const CloseModal = () => {
    setStatus(false);
  };
  if (status === false) return <div></div>;
  else
    return (
      <div className='modal'>
        <div className='modal-title'>game start</div>
        <div className='modal-content'>
          <fieldset>
            <legend>game option</legend>
            <div>
              <input type='radio' name='drone' id='none' value='none'></input>
              <label>none</label>
            </div>
            <div>
              <input type='radio' name='drone' id='map' value='map'></input>
              <label>map option</label>
            </div>
            <div>
              <input type='radio' name='drone' id='power' value='power'></input>
              <label>power option</label>
            </div>
          </fieldset>
        </div>
        <div className='modal-select'>
          <button>regist</button>
          <button onClick={CloseModal}>close</button>
        </div>
      </div>
    );
}

export default GameStartModal;
