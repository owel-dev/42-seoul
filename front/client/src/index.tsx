import React from 'react';
import ReactDOM from 'react-dom/client';
import 'styles/index/index.css';
import Layout from 'components/layout/Layout';
import {BrowserRouter } from 'react-router-dom';

const root = ReactDOM.createRoot(
  document.getElementById('root') as HTMLElement
);
root.render(
  <React.StrictMode>
    <BrowserRouter>
      <Layout />   
    </BrowserRouter>
  </React.StrictMode>
);