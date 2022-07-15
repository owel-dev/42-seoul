import axios from 'axios';
import { useState, useEffect } from 'react';
import { channelListTypes, channelTypes } from 'types/LobbyTypes';
import { DUMMY_SERVER } from 'utils/dummy';
import ChannelListRow from 'components/lobby/ChannelListRow';
import 'styles/Lobby/ChannelList.css';

function ChannelList() {
  const [channelList, setChannelList] = useState<channelListTypes | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get(DUMMY_SERVER + 'channel', {
          headers: {
            'Content-Type': 'application/json',
          },
        });
        setChannelList(getAPI.data);
      } catch (e) {}
    };
    fetchData();
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
