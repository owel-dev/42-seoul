import { modalState } from "utils/recoil/modalState";
import { selector, useRecoilState } from "recoil";
import "styles/modal/Modal.css";
import React from "react";

function Modal({ children }: { children: React.ReactNode }) {
  const [status, setStatus] = useRecoilState(modalState);
  const CloseModal = () => {
    setStatus(false);
  };

  if (status === false) return <div></div>;
  else
    return (
      <div className="modal">
        <div className="modal-title">제목 영역</div>
        <div className="modal-content">
          <div>{children}</div>
        </div>
        <div className="modal-select">
          버튼 영역
          <button onClick={CloseModal}>close</button>
        </div>
      </div>
    );
}
export default Modal;
