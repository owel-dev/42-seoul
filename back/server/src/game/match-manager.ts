import { Injectable } from "@nestjs/common";
import e from "express";
import { Socket } from "socket.io";

@Injectable()
export class MatchManager {
    matchQueue = {};

    addUser(socket: Socket, remakeMode: string, nickName: string, password: string, gameMode: string) {
        // console.log("mode", mode);

        if (this.matchQueue[remakeMode] === undefined) {
            this.matchQueue[remakeMode] = [{
                socketId: socket.id,
                socket: socket,
                nickName: nickName,
                password: password,
                gameMode: gameMode,
            }];
            // console.log(gameMode);
            // console.log(this.matchQueue);
            return;
        }

        this.matchQueue[remakeMode].push({
            socketId: socket.id,
            socket: socket,
            nickName: nickName,
            password: password,
            gameMode: gameMode,
        })
        // console.log(this.matchQueue);
    }

    isTwoUser(mode: string) {
        if (this.matchQueue[mode].length === 2) {
            return true;
        }
        return false;
    }

    getMatchData(mode: string) {
        return (
            {
                firstSocket: this.matchQueue[mode][0].socket,
                firstNick: this.matchQueue[mode][0].nickName,
                secondSocket: this.matchQueue[mode][1].socket,
                secondNick: this.matchQueue[mode][1].nickName,
                gameMode: this.matchQueue[mode][0].gameMode,
                password: this.matchQueue[mode][0].password,
            }
        )
    }

    clearQueue(mode: string) {
        // console.log("#1 clearQueue:", this.matchQueue[mode]);
        delete this.matchQueue[mode];
        // console.log("#2 clearQueue:", this.matchQueue[mode]);
    }
}
