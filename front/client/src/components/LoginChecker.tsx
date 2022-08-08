import { useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { useRecoilState } from 'recoil';
import { loginState } from 'utils/recoil/login';
import Login from 'pages/Login';

interface LoginCheckerProps {
  children: React.ReactNode;
}

export default function LoginChecker({ children }: LoginCheckerProps) {
  const [isLoggedIn, setIsLoggedIn] = useRecoilState(loginState);
  const accessToken = window.location.href
    .split('?accessToken=')[1]
    ?.split('&refreshToken=')[0];
  const refreshToken = window.location.href.split('&refreshToken=')[1];
  const navigate = useNavigate();
  
  useEffect(() => {
    if (accessToken) {
      localStorage.setItem('accessToken', accessToken);
      localStorage.setItem('refreshToken', refreshToken);
    }
    if (localStorage.getItem('accessToken')) setIsLoggedIn(true);
  }, []);

  useEffect(() => {
    const currentURL = window.location.search;
    if (currentURL.includes('?accessToken')) {
      navigate('');
    }
  }, [window.location.href]);

  return isLoggedIn ? <>{children}</> : <Login />;
}
