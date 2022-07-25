import axios from 'axios';

// const baseURL: any = `${process.env.NEXT_PUBLIC_SERVER_ENDPOINT}`;
const baseURL: any = `http://10.19.226.233:3000`;

const instance = axios.create({ baseURL });

instance.interceptors.request.use(
  function setConfig(parameter) {
    const config = parameter;

    config.headers = {
      'Content-Type': 'application/json',
      Authorization: `Bearer ${localStorage.getItem('trans-token')}`,
    };
    return config;
  },
  function getError(error) {
    return Promise.reject(error);
  }
);

export default instance;
