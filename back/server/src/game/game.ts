import { first } from 'rxjs';
import { Server } from 'socket.io';

const uuid = require('uuid');

const MAX_SCORE = 10;
const HERZ = 60;
const COUNTDOWN = 5;

export class Game {
  channelId: string;
  firstPlayer: any;
  secondPlayer: any;
  password: string;
  gameMode: string;
  ball: any;
  server: Server;
  interval: any;
  stopSignal: number;
  stopUser: string;
  maxSpeed: number;
  minSpeed: number;

  constructor(data: any, server: Server) {
    this.channelId = uuid.v4();
    this.firstPlayer = {
      socket: data.firstSocket,
      nickName: data.firstNick,
      score: 0,
      paddlePosition: 50,
    };
    this.secondPlayer = {
      socket: data.secondSocket,
      nickName: data.secondNick,
      score: 0,
      paddlePosition: 50,
    };
    this.password = data.password;
    this.maxSpeed = 2;
    this.minSpeed = 2;
    this.gameMode = data.gameMode;
    if (this.gameMode == 'power') {
      this.maxSpeed = 5;
      this.minSpeed = 5;
    }
    this.ball = {
      x: 20,
      y: 50,
      speed: this.minSpeed,
      direction: 0,
    };
    this.server = server;
    this.stopSignal = 0;
    this.stopUser = '';
  }

  sleep(ms) {
    return new Promise((resolve) => setTimeout(resolve, ms));
  }

  async startGame(): Promise<any> {
    this.server.emit('gamelist-update');
    await this.countDown();
    return new Promise((resolve) => {
      this.interval = setInterval(() => {
        this.update();

        if (
          this.firstPlayer.score == MAX_SCORE ||
          this.secondPlayer.score == MAX_SCORE
        )
          resolve(this.stopGame());

        if (this.stopSignal) resolve(this.stopGame(this.stopUser));

        const data = {
          firstPlayerScore: this.firstPlayer.score,
          secondPlayerScore: this.secondPlayer.score,
          firstPlayerPaddle: this.firstPlayer.paddlePosition,
          secondPlayerPaddle: this.secondPlayer.paddlePosition,
          ball: { x: this.ball.x, y: this.ball.y },
        };

        this.secondPlayer.socket.emit('game-data', data, (callback) => {
          this.secondPlayer.paddlePosition = callback;
        });

        this.firstPlayer.socket.emit('game-data', data, (callback) => {
          this.firstPlayer.paddlePosition = callback;
        });
        // console.log('first: ', this.firstPlayer.socket.id);
        // console.log('second: ', this.secondPlayer.socket.id);
        // console.log("@@@server", server);
        // console.log("@@@channelId", this.channelId);
        this.server
          .to(this.channelId)
          .except([this.firstPlayer.socket.id, this.secondPlayer.socket.id])
          .emit('spectate-data', data);
        // console.log("interval");
      }, (1 / HERZ) * 1000);
    });
  }

  onStopSignal(user: string) {
    this.stopSignal = 1;
    this.stopUser = user;
    return;
  }

  async stopGame(user: string = '') {
    let gameData;
    await clearInterval(this.interval);

    if (
      this.firstPlayer.score === MAX_SCORE ||
      user === this.secondPlayer.nickName
    ) {
      gameData = {
        winPlayer: this.firstPlayer.nickName,
        winScore: this.firstPlayer.score,
        losePlayer: this.secondPlayer.nickName,
        loseScore: this.secondPlayer.score,
        gameMode: this.gameMode,
      };
    }
    if (
      this.secondPlayer.score === MAX_SCORE ||
      user === this.firstPlayer.nickName
    ) {
      gameData = {
        winPlayer: this.secondPlayer.nickName,
        winScore: this.secondPlayer.score,
        losePlayer: this.firstPlayer.nickName,
        loseScore: this.firstPlayer.score,
        gameMode: this.gameMode,
      };
    }
    this.firstPlayer.socket.emit('game-end', gameData.winPlayer);
    this.secondPlayer.socket.emit('game-end', gameData.winPlayer);
    this.server.to(this.channelId).emit('game-end', gameData.winPlayer);
    return gameData;
  }

  async countDown() {
    this.firstPlayer.socket.emit('game-wait', {
      channelId: this.channelId,
      firstPlayer: this.firstPlayer.nickName,
      secondPlayer: this.secondPlayer.nickName,
    });

    this.secondPlayer.socket.emit('game-wait', {
      channelId: this.channelId,
      firstPlayer: this.firstPlayer.nickName,
      secondPlayer: this.secondPlayer.nickName,
    });

    for (let i = COUNTDOWN; i >= 0; --i) {
      // console.log(i.toString());
      this.firstPlayer.socket.emit('count-down', i.toString());
      this.secondPlayer.socket.emit('count-down', i.toString());
      this.server.to(this.channelId).emit('count-down', i.toString());

      if (i == 0) {
        this.firstPlayer.socket.emit('count-down', 'Game Start!');
        this.secondPlayer.socket.emit('count-down', 'Game Start!');
        this.server.to(this.channelId).emit('count-down', 'Game Start!');
      }
      await this.sleep(1000);
    }
  }

  update() {
    this.ball.x += this.ball.speed;
    this.ball.y += this.ball.direction;
    if (this.ball.x >= 100) {
      this.firstPlayer.score++;
      this.reset(1);
    } else if (this.ball.x <= 0) {
      this.secondPlayer.score++;
      this.reset(2);
    }

    if (this.ball.y >= 100) {
      this.ball.direction *= -1;
      this.ball.y = 99;
    } else if (this.ball.y <= 0) {
      this.ball.direction *= -1;
      this.ball.y = 1;
    }
    if (
      this.ball.y < this.secondPlayer.paddlePosition + 10 &&
      this.ball.y + 2 > this.secondPlayer.paddlePosition - 10 &&
      this.ball.x > 93 &&
      this.ball.x < 98
    ) {
      this.ball.x = 93;
      var relativeIntersectY =
        this.secondPlayer.paddlePosition - this.ball.y - 1;
      var normalizedRelativeIntersectionY = relativeIntersectY / 10;
      this.ball.speed = -(
        (1 - Math.abs(normalizedRelativeIntersectionY)) *
          (this.maxSpeed - this.minSpeed) +
        this.minSpeed
      );
      this.ball.direction = -normalizedRelativeIntersectionY;
      //* 테스트용
      // this.ball_velocity[1] = 0;
    } else if (
      this.ball.y < this.firstPlayer.paddlePosition + 10 &&
      this.ball.y + 2 > this.firstPlayer.paddlePosition - 10 &&
      this.ball.x < 9 &&
      this.ball.x > 2
    ) {
      this.ball.x = 9;
      var relativeIntersectY =
        this.firstPlayer.paddlePosition - this.ball.y - 1;
      var normalizedRelativeIntersectionY = relativeIntersectY / 10;
      var normalizedRelativeIntersectionY = relativeIntersectY / 10;
      this.ball.speed =
        (1 - Math.abs(normalizedRelativeIntersectionY)) *
          (this.maxSpeed - this.minSpeed) +
        this.minSpeed;
      this.ball.direction = -normalizedRelativeIntersectionY;
      //* 테스트용
      // this.ball_velocity[1] = 0;
    }
  }

  reset(player) {
    if (player == 1) {
      this.ball.x = 50;
      this.ball.y = 50;
      this.ball.speed = -(this.minSpeed - 1);
      this.ball.direction = 0;
      //* 테스트용
      //this.ball_velocity = [MAX_SPEED, MAX_SPEED];
    } else {
      this.ball.x = 50;
      this.ball.y = 50;
      this.ball.speed = this.minSpeed - 1;
      this.ball.direction = 0;
    }
  }
}
