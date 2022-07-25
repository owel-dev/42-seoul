import { socket } from 'components/layout/Layout';
import { useState, useEffect } from 'react';
import { channelListTypes, channelTypes } from 'types/LobbyTypes';
import ChannelListRow from 'components/lobby/ChannelListRow';
import 'styles/Lobby/Lobby.css';

function ChannelList() {
  const [channelList, setChannelList] = useState<channelListTypes | null>(null);

  useEffect(() => {
    socket.emit('gamelist-request', (response: any) => {
      setChannelList(response);
    });
  }, []);

  return (
    <>
      {channelList?.channelList.map((element: channelTypes, index) => (
        <ChannelListRow key={index} props={element} />
      ))}
    </>
  );
}
export default ChannelList;
