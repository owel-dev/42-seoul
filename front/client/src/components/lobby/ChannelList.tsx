import { useState, useEffect } from 'react';
import ChannelListRow from 'components/lobby/ChannelListRow';
import { socket } from 'components/layout/Layout';
import { channelListTypes, channelTypes } from 'types/LobbyTypes';
import 'styles/Lobby/Lobby.css';

function ChannelList() {
  const [channelList, setChannelList] = useState<channelListTypes | null>(null);

  useEffect(() => {
    socket.on('gamelist-update', () => {
      socket.emit('gamelist-request', '', (response: channelListTypes) => {
        setChannelList(response);
      });
    });
    socket.emit('gamelist-request', '', (response: channelListTypes) => {
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
