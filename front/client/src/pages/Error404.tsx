import { useSetRecoilState } from 'recoil';
import { useEffect } from 'react';
import { errorState } from 'utils/recoil/error';
import Error from 'pages/Error';

const Error404 = () => {
  const setErrorMessage = useSetRecoilState(errorState);

  useEffect(() => {
    setErrorMessage('E404');
  }, []);
  return <Error />;
};

export default Error404;
