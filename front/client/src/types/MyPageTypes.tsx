export type userInfo = {
    user : {
        intraId : string,
        avatar : string, 
        nickName : string,
        win : number,
        lose : number,
        winRate : string
    }
}

export type matchList = {
    matchList:
    [
        {
            player1: string,
            player2: string,
            playerScore1: number,
            playerScore2: number
        }
    ]
}

export type friendList = {
    friendList:
    [
        {
            nickName: string,
            status: string
        }
    ]
}