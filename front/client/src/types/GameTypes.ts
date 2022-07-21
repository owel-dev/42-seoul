export type channelType = {
  channelId: string | null;
  firstPlayer: string | null;
  secondPlayer: string | null;
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
