// export const DUMMY_SERVER = 'http://10.19.247.186:3000';
export const DUMMY_SERVER = 'http://10.19.236.57:3000';
export const DUMMY_USER = {
  intraId: 'yongwkim',
  avatar:
    'https://upload.wikimedia.org/wikipedia/commons/2/2c/Rotating_earth_%28large%29.gif',
  nickName: 'yongwkim',
  win: 5,
  lose: 5,
  winRate: '50%',
};
export const DUMMY_FRIENDS = {
  friendList: [
    {
      nickName: 'kim',
      status: 'online',
    },
    {
      nickName: 'lee',
      status: 'offline',
    },
    {
      nickName: 'park',
      status: 'online',
    },
    {
      nickName: 'choi',
      status: 'ingame',
    },
  ],
};
export const DUMMY_MATCH = {
  matchList: [
    {
      player1: 'hello',
      player2: 'bye',
      playerScore1: 7,
      playerScore2: 4,
    },
    {
      player1: 'hello',
      player2: 'zzz',
      playerScore1: 6,
      playerScore2: 5,
    },
    {
      player1: 'hello',
      player2: 'qapla',
      playerScore1: 2,
      playerScore2: 9,
    },
  ],
};

export const DUMMY_PLAYER = {
  players: [
    {
      player: 'yongwkim',
      avatar: 'https://cdn.intra.42.fr/users/norminet.jpeg',
    },
    {
      player: 'samin',
      avatar: 'https://cdn.intra.42.fr/users/norminet.jpeg',
    },
  ],
};
export const DUMMY_CHANNELS = {
  channelList: [
    {
      channelId: '0',
      player1: 'test',
      player2: 'vvv',
      curNumUsers: 2,
      maxUser: 8,
      password: null,
    },
    {
      channelId: '1',
      player1: 'ppp',
      player2: 'lll',
      curNumUsers: 5,
      maxUser: 8,
      password: '0000',
    },
  ],
};
