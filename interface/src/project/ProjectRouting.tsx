import { FC } from 'react';
import { Navigate, Routes, Route } from 'react-router-dom';

import DemoProject from './DemoProject';

const ProjectRouting: FC = () => {
  return (
    <Routes>
      <Route path="/*" element={<DemoProject />} />
    </Routes>
  );
};

export default ProjectRouting;
