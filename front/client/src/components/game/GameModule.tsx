import { MouseEvent, useEffect, useRef } from 'react';
import { useRecoilState } from 'recoil';
import { socket } from 'components/layout/Layout';
import { countState, gameState } from 'utils/recoil/gameState';
import 'styles/game/Game.css';

let mouseState = 0;
let pingTime = 0;

function GameModule(props: { gameMode: string }) {
  const canvas = useRef<HTMLCanvasElement>(null);
  const background = useRef<HTMLCanvasElement>(null);
  const [gameData, setGameData] = useRecoilState(gameState);
  const [countData, setCountData] = useRecoilState(countState);

  function draw_background(
    ctx: CanvasRenderingContext2D,
    width: number,
    height: number,
    img: string
  ) {
    if (img === 'map') {
      const image = new Image();
      image.src = '/galaxy.jpg';
      image.onload = function () {
        ctx.drawImage(image, 0, 0, width, height);
      };
    } else if (img === 'power') {
      ctx.fillStyle = 'black';
      ctx.fillRect(0, 0, width, height);
      draw_text(ctx, 'POWER!', Math.floor(width / 2), 50);
    } else {
      ctx.fillStyle = 'black';
      ctx.fillRect(0, 0, width, height);
    }
  }

  function draw_ball(ctx: CanvasRenderingContext2D, x: number, y: number) {
    ctx.beginPath();
    ctx.arc(x, y, 10, 0, Math.floor(Math.PI * 2));
    ctx.fillStyle = 'white';
    ctx.fill();
    ctx.closePath();
  }

  function draw_paddle(
    ctx: CanvasRenderingContext2D,
    x: number,
    y: number,
    width: number,
    height: number
  ) {
    ctx.fillStyle = 'white';
    ctx.fillRect(x, y, width, height);
  }

  function draw_text(
    ctx: CanvasRenderingContext2D,
    text: string,
    width: number,
    height: number
  ) {
    ctx.textAlign = 'center';
    ctx.font = '40pt pira';
    ctx.fillStyle = 'white';
    ctx.strokeText(text, width, height);
    ctx.fillText(text, width, height);
  }

  function saveMouseState(event: MouseEvent) {
    const canvasEle = canvas.current as HTMLCanvasElement;
    const ratio: number = canvasEle.height / canvasEle.clientHeight;

    mouseState = event.nativeEvent.offsetY * ratio;
  }

  useEffect(() => {
    const canvasEle = background.current!;
    const ctx = canvasEle.getContext('2d')!;

    draw_background(ctx, canvasEle.width, canvasEle.height, props.gameMode);
  }, []);

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
    const canvasEle = canvas.current!;
    const ctx = canvasEle.getContext('2d')!;
    const displayWidth = canvasEle.width;
    const displayHeight = canvasEle.height;

    ctx.clearRect(0, 0, displayWidth, displayHeight);
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
    const canvasEle = canvas.current!;
    const ctx = canvasEle.getContext('2d')!;
    const displayWidth = canvasEle.width;
    const displayHeight = canvasEle.height;

    ctx.clearRect(0, 0, displayWidth, displayHeight);
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
        ref={background}
        height='400px'
        width='700px'
        id='background-layer'
      />
      <canvas
        ref={canvas}
        height='400px'
        width='700px'
        onMouseMove={saveMouseState}
        id='game-layer'
      />
      <div style={{ position: 'absolute', top: '70%', left: '35%' }}>
        ping : {pingTime}
      </div>
    </div>
  );
}
export default GameModule;
