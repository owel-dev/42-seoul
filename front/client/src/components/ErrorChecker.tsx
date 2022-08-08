import { useRecoilValue } from 'recoil';
import { errorState } from 'utils/recoil/error';
import Error from 'pages/Error';

interface ErrorCheckerProps {
  children: React.ReactNode;
}

export default function ErrorChecker({ children }: ErrorCheckerProps) {
  const errorMessage = useRecoilValue(errorState);

  return errorMessage === '' ? <>{children}</> : <Error />;
}
