export type profileType = {
  intraId: string;
  avatar: string;
  nickName: string;
  win: number;
  lose: number;
  winRate: string;
  isFriend: boolean;
};

export type matchList = {
  matchList: [
    {
      player1: string;
      player2: string;
      score1: number;
      score2: number;
      mode: string;
    }
  ];
};

export type friendList = {
  friendList: [
    {
      nickName: string;
      status: string;
      channelId: string;
    }
  ];
};
