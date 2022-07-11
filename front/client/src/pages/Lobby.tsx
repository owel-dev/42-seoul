import ChannelList from "components/lobby/ChannelList";
import 'styles/Lobby/Lobby.css'

function Lobby() {
    return (
        <div className='lobby'>
            <h1>Lobby</h1>
            <button>game start</button>
            <ChannelList />
        </div>
    )
}
export default Lobby;