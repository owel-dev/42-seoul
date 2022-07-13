const dummy = ['message01', 'message02', 'message03'];

function ChatList() {
  return (
    <div className='chat-list'>
      {dummy.map((element, index) => {
        return (
          <div className='userlist-row' key={index}>
            {element}
          </div>
        );
      })}
    </div>
  );
}
export default ChatList;
