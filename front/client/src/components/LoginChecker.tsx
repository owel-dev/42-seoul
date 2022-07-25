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
  const token = window.location.href.split('?token=')[1];
  const navigate = useNavigate();

  useEffect(() => {
    if (token) localStorage.setItem('trans-token', token);
    if (localStorage.getItem('trans-token')) setIsLoggedIn(true);
  }, []);

  useEffect(() => {
    const currentURL = window.location.search;
    if (currentURL.includes('token')) {
      navigate('');
    }
  }, [window.location.href]);

  return isLoggedIn ? <>{children}</> : <Login />;
}
