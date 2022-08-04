import { Injectable } from "@nestjs/common";
import e from "express";
import { Socket } from "socket.io";

@Injectable()
export class MatchManager {
    matchQueue = {};

    addUser(socket: Socket, gameMode: string, nickName: string, password: string) {
        // console.log("mode", mode);
        if (this.matchQueue[gameMode] === undefined) {
            this.matchQueue[gameMode] = [{
                socketId: socket.id,
                socket: socket,
                nickName: nickName,
                password: password
            }];
            // console.log(gameMode);
            // console.log(this.matchQueue);
            return;
        }
        this.matchQueue[gameMode].push({
            socketId: socket.id,
            socket: socket,
            nickName: nickName,
            password: password
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
