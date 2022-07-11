import "styles/Lobby/ChannelList.css";
import { channelListTypes, channelTypes } from "types/LobbyTypes";
import ChannelListRow from "components/lobby/ChannelListRow";
import { useState, useEffect } from "react";
import axios from "axios";

// const dummy = {
//   channelList: [
//     {
//       channelId: "#aaa",
//       player1: "test",
//       player2: "vvv",
//       curNumUsers: 2,
//       maxUser: 8,
//       password: null,
//     },
//     {
//       channelId: "#bbb",
//       player1: "ppp",
//       player2: "lll",
//       curNumUsers: 5,
//       maxUser: 8,
//       password: "0000",
//     },
//   ],
// };

function ChannelList() {
  const [channelList, setChannelList] = useState<channelListTypes | null>(null);
  useEffect(() => {
    const fetchData = async () => {
      try {
        const getAPI = await axios.get("http://localhost:3000/channel", {
          headers: {
            "Content-Type": "application/json",
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
