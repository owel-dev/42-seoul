import { Route, Routes } from 'react-router-dom';
import Nav from 'components/layout/Nav';
import Side from 'components/layout/Side';
import Content from 'components/layout/Content';
import Rank from 'pages/Rank';

function Layout()
{
    return (
        <div>
            <Nav />
            <Side />
            <Content>
                <Routes>
                    <Route path="ranking" element={<Rank />} />
                </Routes>
            </Content>

        </div>
    )
}

export default Layout;
