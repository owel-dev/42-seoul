import ChannelList from 'components/lobby/ChannelList';
import Modal from 'components/modal/Modal';
import GameStartModal from 'components/modal/GameStartModal';
import { gameStartModalState } from 'utils/recoil/modalState';
import { useSetRecoilState } from 'recoil';

import 'styles/Lobby/Lobby.css';

function Lobby() {
  const setGameModalState = useSetRecoilState(gameStartModalState);
  const openGameModal = () => {
    setGameModalState(true);
  };

  return (
    <div className='lobby'>
      <h1>Lobby</h1>
      <button onClick={openGameModal}>game start</button>
      <Modal>
        <GameStartModal />
      </Modal>
      <ChannelList />
    </div>
  );
}
export default Lobby;
