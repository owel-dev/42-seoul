export type channelTypes = {
  channelId: string;
  player1: string;
  player2: string;
  curNumUser: number;
  maxUser: number;
  password: string | null;
  type: number;
  mode: number;
};

export type channelListTypes = {
  channelList: channelTypes[];
};
