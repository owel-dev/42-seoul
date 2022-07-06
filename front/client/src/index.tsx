import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import Nav from './Nav';
import Side from './Side';
import Content from './Content';
import Rank from './Rank';
import reportWebVitals from './reportWebVitals';
import { Route, Routes, BrowserRouter } from 'react-router-dom';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <BrowserRouter>
      <Nav></Nav>
      <Side></Side>
      <Content>
        <Routes>
          <Route path="ranking" element={<Rank></Rank>}></Route>
        </Routes>
      </Content>
    </BrowserRouter>
  </React.StrictMode>
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
