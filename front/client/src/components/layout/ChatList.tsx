import { useRecoilValue, useSetRecoilState } from 'recoil';
import { chat } from 'types/chatTypes';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';

function ChatList({ chatList }: { chatList: chat[] }) {
  const myData = useRecoilValue(myDataState);
  const setModalInfo = useSetRecoilState(modalState);

  return (
    <>
      {chatList?.map((element, index) => (
        <div
          className={element.isDM ? 'directMessage' : 'messageList'}
          key={index}
        >
          <span
            className={
              element.nickName === myData.nickName ? 'myNick' : 'userNick'
            }
            onClick={() =>
              element.nickName !== myData.nickName &&
              setModalInfo({ modalName: 'SIDE-USER', user: element.nickName })
            }
          >
            {`${element.nickName} `}
          </span>
          {/* <span className={element.isDM ? 'directMessage' : 'messageList'}> */}
          {`- ${element.message}`}
          {/* </span> */}
        </div>
      ))}
    </>
  );
}

export default ChatList;
