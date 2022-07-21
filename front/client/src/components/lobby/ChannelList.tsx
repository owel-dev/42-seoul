import { socket } from 'App';
import { useState, useEffect } from 'react';
import { channelListTypes, channelTypes } from 'types/LobbyTypes';
import ChannelListRow from 'components/lobby/ChannelListRow';
import 'styles/Lobby/ChannelList.css';

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
