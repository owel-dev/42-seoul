import { useState, useEffect } from 'react';
import { channelListTypes, channelTypes } from 'types/LobbyTypes';
import { DUMMY_SERVER } from 'utils/dummy';
import instance from 'utils/axios';
import ChannelListRow from 'components/lobby/ChannelListRow';
import 'styles/lobby/ChannelList.css';

function ChannelList() {
  const [channelList, setChannelList] = useState<channelListTypes | null>(null);

  useEffect(() => {
    fetchData();
  }, []);

  const fetchData = async () => {
    try {
      const getAPI = await instance.get(`/channel`);
      setChannelList(getAPI.data);
    } catch (e) {}
  };

  return (
    <>
      {channelList?.channelList.map((element: channelTypes, index) => (
        <ChannelListRow key={index} props={element} />
      ))}
    </>
  );
}
export default ChannelList;
