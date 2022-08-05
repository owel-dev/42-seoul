import { tsConstructorType } from '@babel/types';
import { NotFoundException, OnModuleInit } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { timeStamp } from 'console';
import { resolve } from 'path';
import { Server, Socket } from 'socket.io';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';

const uuid = require('uuid');

let MAX_SPEED = 2;
let MIN_SPEED = 2;
const MAX_SCORE = 10;
const HERZ = 60;
const COUNTDOWN = 5;

// let interval;

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

    constructor(
        data: any,
        server: Server,
        // @InjectRepository(User)
        // private userRepository: Repository<User>,
    ) {
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
        this.gameMode = data.gameMode;
        if (this.gameMode == 'power') {
            MAX_SPEED = 5;
            MIN_SPEED = 5;
        }
        this.ball = {
            x: 20,
            y: 50,
            speed: MIN_SPEED,
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
        await this.countDown();
        return new Promise((resolve) => {
            this.interval = setInterval(() => {
                this.update();

                if (this.firstPlayer.score == MAX_SCORE ||
                    this.secondPlayer.score == MAX_SCORE)
                    resolve(this.stopGame());

                if (this.stopSignal)
                    resolve(this.stopGame(this.stopUser));

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
                this.server.to(this.channelId).emit('game-data', data);
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
        await clearInterval(this.interval);
        this.firstPlayer.socket.emit('game-end', this.channelId);
        this.secondPlayer.socket.emit('game-end', this.channelId);
        this.server.to(this.channelId).emit('game-end', this.channelId);

        if (user === this.firstPlayer.nickName || this.firstPlayer.score === MAX_SCORE) {
            return {
                win: this.firstPlayer.nickName,
                lose: this.secondPlayer.nickName,
            };
        }
        else if (user === this.secondPlayer.nickName || this.secondPlayer.score === MAX_SCORE) {
            return {
                win: this.secondPlayer.nickName,
                lose: this.firstPlayer.nickName,
            };
        }

        return new NotFoundException("stopGame");
    }

    sendGameData() {
        // this.interval = setInterval(() => {
        //     this.update();
        //     if (this.firstPlayer.score == 10 ||
        //         this.secondPlayer.score == 10) {
        //         this.stopGame();
        //     }
        //     const data = {
        //         firstPlayerScore: this.firstPlayer.score,
        //         secondPlayerScore: this.secondPlayer.score,
        //         firstPlayerPaddle: this.firstPlayer.paddlePosition,
        //         secondPlayerPaddle: this.secondPlayer.paddlePosition,
        //         ball: { x: this.ball.x, y: this.ball.y },
        //     };
        //     this.secondPlayer.socket.emit(
        //         'game-data',
        //         data,
        //         (callback) => {
        //             this.secondPlayer.paddlePosition = callback;
        //         },
        //     );
        //     this.firstPlayer.socket.emit(
        //         'game-data',
        //         data,
        //         (callback) => {
        //             this.firstPlayer.paddlePosition = callback;
        //         },
        //     );
        //     // console.log("@@@server", server);
        //     // console.log("@@@channelId", this.channelId);
        //     this.server.to(this.channelId).emit('game-data', data);
        //     // console.log("interval");
        // }, (1 / HERZ) * 1000);
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
            console.log(i.toString());
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
                (MAX_SPEED - MIN_SPEED) +
                MIN_SPEED
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
                (MAX_SPEED - MIN_SPEED) +
                MIN_SPEED;
            this.ball.direction = -normalizedRelativeIntersectionY;
            //* 테스트용
            // this.ball_velocity[1] = 0;
        }
    }

    reset(player) {
        if (player == 1) {
            this.ball.x = 50;
            this.ball.y = 50;
            this.ball.speed = -(MIN_SPEED - 1);
            this.ball.direction = 0;
            //* 테스트용
            //this.ball_velocity = [MAX_SPEED, MAX_SPEED];
        } else {
            this.ball.x = 50;
            this.ball.y = 50;
            this.ball.speed = MIN_SPEED - 1;
            this.ball.direction = 0;
        }
    }
}
