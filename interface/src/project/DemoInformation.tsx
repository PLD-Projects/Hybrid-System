import { FC } from 'react';

import ReactFlow from 'react-flow-renderer';

import { Box } from '@mui/material';

import {defaultNodes,defaultEdges} from './nodes';
import {Edges} from './edges';

import './css/reactflow.css';

import GridNode from './CustomNodes/GridNode';
import BatNode from './CustomNodes/BatNode';
import InvNode from './CustomNodes/InvNode';
import TsNode from './CustomNodes/TsNode';
import LoadNode from './CustomNodes/LoadNode';
import GInvNode from './CustomNodes/GInvNode';
import PvNode from './CustomNodes/PvNode';

const nodeTypes = {
  GridNode: GridNode,
  BatNode: BatNode,
  InvNode: InvNode,
  TsNode: TsNode,
  LoadNode:LoadNode,
  GInvNode:GInvNode,
  PvNode:PvNode,
};

export const DRAWER_WIDTH = 112;

const edgeOptions = {
  animated: true,
  style: {
    stroke: 'green',
  },
};

const connectionLineStyle = { stroke: 'white' };

const DemoInformation: FC = () => {
  const edge = Edges();
  return (
    <>
      <Box
        position="relative"
        sx={{height:{xs:'85vh', lg:'90vh'},}}
      >
        <ReactFlow
          nodes={defaultNodes}
          edges={edge.defaultEdges}
          // defaultNodes={defaultNodes}
          // defaultEdges={defaultEdges}
          defaultEdgeOptions={edgeOptions}
          nodeTypes={nodeTypes}
          panOnDrag={false}
          zoomOnScroll={false}
          nodesDraggable={false}
          nodesConnectable={false}
          fitView
          // style={{
          //   backgroundColor: '#D3D2E5',
          // }}
          connectionLineStyle={connectionLineStyle}
        />
      </Box>
    </>
  );
};

export default DemoInformation;
