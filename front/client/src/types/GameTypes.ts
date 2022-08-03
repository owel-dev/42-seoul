export type channelType = {
  channelId: string;
  firstPlayer: string;
  secondPlayer: string;
};

export type gameType = {
  firstPlayerScore: number;
  secondPlayerScore: number;
  firstPlayerPaddle: number;
  secondPlayerPaddle: number;
  ball: {
    x: number;
    y: number;
  };
};

export type inviteType = {
  gameMode: string;
  nickName: string;
  password: string;
  oppNickName: string;
};
