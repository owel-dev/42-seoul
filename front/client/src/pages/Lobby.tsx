import { useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import ChannelList from 'components/lobby/ChannelList';
import 'styles/lobby/Lobby.css';

function Lobby() {
  const setModalInfo = useSetRecoilState(modalState);

  const openGameModal = () => {
    setModalInfo({ modalName: 'MAIN-START' });
  };

  return (
    <div className='lobby'>
      <h1>Lobby</h1>
      <button onClick={openGameModal}>game start</button>
      <ChannelList />
    </div>
  );
}
export default Lobby;
