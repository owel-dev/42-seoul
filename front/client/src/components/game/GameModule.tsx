import { socket } from 'App';
import { MouseEvent, useEffect, useRef } from 'react';
import { atom, useRecoilState } from 'recoil';

type gameType = {
  firstPlayerScore: number;
  secondPlayerScore: number;
  firstPlayerPaddle: number;
  secondPlayerPaddle: number;
  ball: {
    x: number;
    y: number;
  };
};

export const gameState = atom<gameType>({
  key: 'gameState',
  default: {
    firstPlayerScore: 0,
    secondPlayerScore: 0,
    firstPlayerPaddle: 0,
    secondPlayerPaddle: 0,
    ball: {
      x: 0,
      y: 0,
    },
  },
});
export const countState = atom<string>({
  key: 'countState',
  default: '',
});

let mouseState = 0;

function GameModule() {
  function draw_background(ctx: any, canvasEle: any) {
    ctx.clearRect(0, 0, canvasEle.width, canvasEle.height);
    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, canvasEle.width, canvasEle.height);
  }
  function draw_ball(ctx: any, x: number, y: number) {
    ctx.beginPath();
    ctx.arc(x, y, 10, 0, Math.PI * 2);
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
    ctx.font = '40pt Fira';
    ctx.fillStyle = 'white';
    ctx.strokeText(text, width, height);
    ctx.fillText(text, width, height);
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
      callback((mouseState / 500) * 100);
    });
    socket.on('game-end', (data) => {
      setCountData('game over');

      //게임 끝난 여부 true
    });
  }, []);

  useEffect(() => {
    //배경
    const canvasEle: any = canvas.current;
    var ctx = canvasEle.getContext('2d');
    draw_background(ctx, canvasEle);
    draw_ball(
      ctx,
      (gameData.ball.x / 100) * canvasEle.width,
      (gameData.ball.y / 100) * canvasEle.height
    );
    draw_paddle(
      ctx,
      0.05 * canvasEle.width,
      ((gameData.firstPlayerPaddle - 10) / 100) * canvasEle.height,
      0.015 * canvasEle.width,
      0.2 * canvasEle.height
    );
    draw_paddle(
      ctx,
      0.945 * canvasEle.width,
      ((gameData.secondPlayerPaddle - 10) / 100) * canvasEle.height,
      0.015 * canvasEle.width,
      0.2 * canvasEle.height
    );

    //스코어1
    draw_text(
      ctx,
      gameData.firstPlayerScore.toString(),
      canvasEle.width / 4,
      50
    );
    //스코어2
    draw_text(
      ctx,
      gameData.secondPlayerScore.toString(),
      canvasEle.width * 0.75,
      50
    );
  });

  useEffect(() => {
    const canvasEle: any = canvas.current;
    var ctx = canvasEle.getContext('2d');
    draw_background(ctx, canvasEle);
    draw_text(ctx, countData, canvasEle.width / 2, canvasEle.height / 2);
  }, [countData]);

  function saveMouseState(event: MouseEvent) {
    mouseState = event.nativeEvent.offsetY;
  }

  return (
    <div>
      <canvas
        ref={canvas}
        height='500px'
        width='700px'
        onMouseMove={saveMouseState}
      ></canvas>
    </div>
  );
}
export default GameModule;
