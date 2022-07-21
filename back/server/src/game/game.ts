const uuid = require('uuid');
const MAX_SPEED = 3;
const MIN_SPEED = 3;
const MAX_SCORE = 10;

export class User {
    socket: any;
    username: string;
    game: any;

    constructor(socket) {
        this.socket = socket;
        this.username = null;
        this.game = { id: null, playing: false };
    }
}

export class Game {
    ball_vel: number;
    id: string;
    player1: string;
    player2: string;
    players: any;
    ball: any;
    ball_velocity: any;
    password: string;
    mode: string;

    constructor(id: string, username: string, id2: string, username2: string, password: string = '', mode: string) {
        this.ball_vel = 0.5;
        this.id = uuid.v4();
        this.player1 = id;
        this.player2 = id2;
        this.players = {};
        this.players[id] = { name: username.toString(), pos: 50, score: 0 };
        this.players[id2] = { name: username2.toString(), pos: 50, score: 0 };
        this.ball = { x: 20, y: 50 };
        this.ball_velocity = [MIN_SPEED, 0];
        this.password = password;
        this.mode = mode;
    };

    update() {
        this.ball.x += this.ball_velocity[0];
        this.ball.y += this.ball_velocity[1];
        if (this.ball.x >= 100) {
            this.players[this.player1].score++;
            this.reset(1);
        } else if (this.ball.x <= 0) {
            this.players[this.player2].score++;
            this.reset(2);
        }

        if (this.ball.y >= 100) {
            this.ball_velocity[1] *= -1;
            this.ball.y = 99;
        } else if (this.ball.y <= 0) {
            this.ball_velocity[1] *= -1;
            this.ball.y = 1;
        }
        if (
            this.ball.y < this.players[this.player2].pos + 10 &&
            this.ball.y + 2 > this.players[this.player2].pos - 10 &&
            this.ball.x > 93 &&
            this.ball.x < 98
        ) {
            this.ball.x = 93;
            var relativeIntersectY =
                this.players[this.player2].pos - this.ball.y - 1;
            var normalizedRelativeIntersectionY = relativeIntersectY / 10;
            this.ball_velocity[0] = -(
                (1 - Math.abs(normalizedRelativeIntersectionY)) *
                (MAX_SPEED - MIN_SPEED) +
                MIN_SPEED
            );
            this.ball_velocity[1] = -normalizedRelativeIntersectionY;
            //* 테스트용
            // this.ball_velocity[1] = 0;
        } else if (
            this.ball.y < this.players[this.player1].pos + 10 &&
            this.ball.y + 2 > this.players[this.player1].pos - 10 &&
            this.ball.x < 9 &&
            this.ball.x > 2
        ) {
            this.ball.x = 9;
            var relativeIntersectY =
                this.players[this.player1].pos - this.ball.y - 1;
            var normalizedRelativeIntersectionY = relativeIntersectY / 10;
            var normalizedRelativeIntersectionY = relativeIntersectY / 10;
            this.ball_velocity[0] =
                (1 - Math.abs(normalizedRelativeIntersectionY)) *
                (MAX_SPEED - MIN_SPEED) +
                MIN_SPEED;
            this.ball_velocity[1] = -normalizedRelativeIntersectionY;
            //* 테스트용
            // this.ball_velocity[1] = 0;
        }
    }

    reset(player) {
        if (player == 1) {
            this.ball.x = 50;
            this.ball.y = 50;
            this.ball_velocity = [-(MIN_SPEED - 1), 0];
            //* 테스트용
            //this.ball_velocity = [MAX_SPEED, MAX_SPEED];
        } else {
            this.ball.x = 50;
            this.ball.y = 50;
            this.ball_velocity = [MIN_SPEED - 1, 0];
        }
    }
}