export type channelTypes = {
  channelId: string;
  player1: string;
  player2: string;
  curNumUsers: number;
  maxUser: number;
  password: string | null;
  type: number;
  mode: number;
};

export type channelListTypes = {
  channelList: channelTypes[];
};
