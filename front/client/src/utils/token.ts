import axios from 'axios';

const refreshToken = async () => {
  try {
    const ret = await axios.get(
      `${process.env.REACT_APP_SERVERIP}/auth-jwt/requestAccessToken`,
      {
        headers: {
          'Content-Type': 'application/json',
          Authorization: `Bearer ${localStorage.getItem('refreshToken')}`,
        },
      }
    );
    localStorage.setItem('accessToken', ret?.data.accessToken);
    if (ret?.data.refreshToken)
      localStorage.setItem('refreshToken', ret?.data.refreshToken);
    return ret;
  } catch (e) {
    throw e;
  }
};

export default refreshToken;
