import axios from 'axios';
import { useSetRecoilState } from 'recoil';
import { DUMMY_SERVER } from 'utils/dummy';
import { modalState } from 'types/modal';
import 'styles/modal/Modal.css';

function GameStartModal() {
  const setModalInfo = useSetRecoilState(modalState);

  const CloseModal = () => {
    setModalInfo({ modalName: null });
  };

  function PostMakeChannel() {
    const fetchData = async () => {
      try {
        const getAPI = await axios.post(DUMMY_SERVER + 'channel', {
          // data: {
          player1: 'yongwkim',
          player2: 'samin',
          intraId: 'yongwkim',
          password: 'asdf',
          mode: 1,
          type: 2,
          // },
        });
        // console.log(getAPI.data);
      } catch (e) {
        // console.log(e);
      }
    };
    fetchData();
  }

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
        <button onClick={PostMakeChannel}>regist</button>
        <button onClick={CloseModal}>close</button>
      </div>
    </div>
  );
}

export default GameStartModal;
