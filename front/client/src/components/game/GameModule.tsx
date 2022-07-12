import { useEffect, useRef } from 'react';

function GameModule() {
  //게임 socket 연결, 1초당 n번 캔버스를 다시 그려준다

  const canvas: any = useRef();
  useEffect(() => {
    const canvasEle: any = canvas.current;
    var ctx = canvasEle.getContext('2d');
    ctx.clearRect(0, 0, canvasEle.width, canvasEle.height);
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, canvasEle.width, canvasEle.height);

    //공
    ctx.beginPath();
    ctx.arc(250, 250, 10, 0, 360);
    ctx.stroke();
    ctx.fillStyle = 'white';
    ctx.fill();

    //바1
    ctx.fillStyle = 'white';
    ctx.fillRect(50, 200, 15, 100);
    //바2
    ctx.fillStyle = 'white';
    ctx.fillRect(450, 200, 15, 100);
  }, []);

  return (
    <div>
      <canvas ref={canvas} height='500px' width='500px'></canvas>
    </div>
  );
}
export default GameModule;
