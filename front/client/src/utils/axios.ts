import axios from 'axios';

const baseURL: string = `${process.env.REACT_APP_SERVERIP}`;

const instance = axios.create({ baseURL });

instance.interceptors.request.use(
  function setConfig(parameter) {
    const config = parameter;

    config.headers = {
      'Content-Type': 'application/json',
      Authorization: `Bearer ${localStorage.getItem('accessToken')}`,
    };
    return config;
  },
  function getError(error) {
    return Promise.reject(error);
  }
);

export default instance;
