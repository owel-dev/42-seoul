import 'styles/Lobby/ChannelList.css';
import { channelListTypes, channelTypes } from 'types/LobbyTypes';
import ChannelListRow from 'components/lobby/ChannelListRow';
import { useState, useEffect } from 'react';
import axios from 'axios';
import { DUMMY_SERVER } from 'utils/dummy';

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
      } catch (e) {
        console.log(e);
      }
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
