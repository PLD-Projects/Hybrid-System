import React, { memo } from 'react';

import { Handle, Position } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';
import ChangeCircleIcon from '@mui/icons-material/ChangeCircle';
import CottageIcon from '@mui/icons-material/Cottage';
import SolarPowerIcon from '@mui/icons-material/SolarPower';

import { Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../api/endpoints';
import { updateValue, useWs } from '../utils';

import { EdgeState } from './types';

export const EDGE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "EdgeState";

export const Edges = () => {
  const WS = useWs<EdgeState>(EDGE_SETTINGS_WEBSOCKET_URL);

  const defaultEdges = [
    { id: 'p2gi', source: 'pv', target: 'ginv',sourceHandle: 'a', targetHandle: 'a', type: 'step', hidden: !WS.data?.p2gi},
    { id: 'p2i', source: 'pv', target: 'inv',sourceHandle: 'b', targetHandle: 'a', type: 'step', hidden: !WS.data?.p2i},
  
    { id: 'gi2g', source: 'ginv', target: 'grid',sourceHandle: 'b', targetHandle: 'a', type: 'step', hidden: !WS.data?.gi2g},
  
    { id: 'g2l', source: 'grid', target: 'load',sourceHandle: 'b', targetHandle: 'a', type: 'step', hidden: !WS.data?.g2l},
    { id: 'g2i', source: 'grid', target: 'inv',sourceHandle: 'c', targetHandle: 'c', type: 'step', hidden: !WS.data?.g2i},
  
    { id: 'i2l', source: 'inv', target: 'load',sourceHandle: 'b', targetHandle: 'b', type: 'step', hidden: !WS.data?.i2l},
    { id: 'i2b', source: 'inv', target: 'bat',sourceHandle: 'd', targetHandle: 'a',type: 'step', hidden: !WS.data?.i2b},
  
    { id: 'b2i', source: 'bat', target: 'inv',sourceHandle: 'b', targetHandle: 'e', type: 'step', hidden: !WS.data?.b2i},
  ];

  return {defaultEdges} as const
};

