export type rankRowType = {
  rank: string;
  nickName: string;
  win: number;
  lose: number;
  winRate: string;
};

export type userRank = {
  ranking: [rankRowType];
};
