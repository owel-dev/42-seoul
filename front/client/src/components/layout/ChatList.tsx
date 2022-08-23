import { useEffect } from 'react';
import { useRecoilValue, useSetRecoilState } from 'recoil';
import { modalState } from 'utils/recoil/modal';
import { myDataState } from 'utils/recoil/myData';
import { chat } from 'types/chatTypes';

function ChatList({ chatList }: { chatList: chat[] }) {
  const myData = useRecoilValue(myDataState);

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
          >
            {element.nickName && `${element.nickName} - `}
          </span>
          {`${element.message}`}
        </div>
      ))}
    </>
  );
}

export default ChatList;
