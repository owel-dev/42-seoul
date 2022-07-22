import { socket } from 'App';
import { MouseEvent, useEffect, useRef } from 'react';
import { useRecoilState } from 'recoil';
import { countState, gameState } from 'utils/recoil/gameState';

let mouseState = 0;
let pingTime = 0;

function GameModule() {
  function draw_background(
    ctx: any,
    canvasEle: any,
    width: number,
    height: number
  ) {
    ctx.clearRect(0, 0, width, height);
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, width, height);
  }

  function draw_ball(ctx: any, x: number, y: number) {
    ctx.beginPath();
    ctx.arc(x, y, 10, 0, Math.floor(Math.PI * 2));
    ctx.fillStyle = 'white';
    ctx.fill();
    ctx.closePath();
  }

  function draw_paddle(
    ctx: any,
    x: number,
    y: number,
    width: number,
    height: number
  ) {
    ctx.fillStyle = 'white';
    ctx.fillRect(x, y, width, height);
  }

  function draw_text(ctx: any, text: string, width: number, height: number) {
    ctx.textAlign = 'center';
    ctx.font = '40pt pira';
    ctx.fillStyle = 'white';
    ctx.strokeText(text, width, height);
    ctx.fillText(text, width, height);
  }

  function saveMouseState(event: MouseEvent) {
    const canvasEle: any = canvas.current;
    const ratio: number = canvasEle.height / canvasEle.clientHeight;
    //캔버스 크기/줄어든 캔버스 실제 크기의 비율
    mouseState = event.nativeEvent.offsetY * ratio;
  }

  const canvas: any = useRef();
  const [gameData, setGameData] = useRecoilState(gameState);
  const [countData, setCountData] = useRecoilState(countState);

  useEffect(() => {
    socket.on('count-down', (data) => {
      setCountData(data);
    });
    socket.on('game-data', (data, callback) => {
      setGameData(data);
      if (typeof callback === 'function') callback((mouseState / 500) * 100);
    });
    socket.on('game-end', () => {
      clearInterval(ping_interval);
      setCountData('game over');
    });
    const ping_interval = setInterval(() => {
      const time = Date.now();
      socket.emit('get-ping', () => {
        pingTime = Date.now() - time;
      });
    }, 500);
  }, [setCountData, setGameData]);

  useEffect(() => {
    const canvasEle: any = canvas.current;
    const ctx = canvasEle.getContext('2d', { alpha: 'false' });
    const displayWidth = canvasEle.width;
    const displayHeight = canvasEle.height;

    draw_background(ctx, canvasEle, displayWidth, displayHeight);
    draw_ball(
      ctx,
      Math.floor((gameData.ball.x / 100) * displayWidth),
      Math.floor((gameData.ball.y / 100) * displayHeight)
    );
    draw_paddle(
      ctx,
      Math.floor(0.05 * displayWidth),
      Math.floor(((gameData.firstPlayerPaddle - 10) / 100) * displayHeight),
      Math.floor(0.015 * displayWidth),
      Math.floor(0.2 * displayHeight)
    );
    draw_paddle(
      ctx,
      Math.floor(0.945 * displayWidth),
      Math.floor(((gameData.secondPlayerPaddle - 10) / 100) * displayHeight),
      Math.floor(0.015 * displayWidth),
      Math.floor(0.2 * displayHeight)
    );
    draw_text(
      ctx,
      gameData.firstPlayerScore.toString(),
      Math.floor(displayWidth / 4),
      50
    );
    draw_text(
      ctx,
      gameData.secondPlayerScore.toString(),
      Math.floor(displayWidth * 0.75),
      50
    );
  });

  useEffect(() => {
    const canvasEle: any = canvas.current;
    const ctx = canvasEle.getContext('2d', { alpha: 'false' });
    const displayWidth = canvasEle.width;
    const displayHeight = canvasEle.height;

    draw_background(ctx, canvasEle, displayWidth, displayHeight);
    draw_text(
      ctx,
      countData,
      Math.floor(displayWidth / 2),
      Math.floor(displayHeight / 2)
    );
  }, [countData]);

  return (
    <div>
      <canvas
        ref={canvas}
        height='500px'
        width='700px'
        style={{ height: '100%', width: '100%' }}
        onMouseMove={saveMouseState}
      />
      <div>ping : {pingTime}</div>
    </div>
  );
}
export default GameModule;
