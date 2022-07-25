import { chat } from 'types/chatTypes';

function ChatList({ chatList }: { chatList: chat[] }) {
  return (
    <>
      {chatList?.map((element, index) => (
        <div
          className={element.isDM ? 'directMessage' : 'messageList'}
          key={index}
        >
          {`${element.nickName} - ${element.message}`}
        </div>
      ))}
    </>
  );
}

export default ChatList;
