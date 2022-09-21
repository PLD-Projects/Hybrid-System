import React, { memo } from 'react';

import { Handle, Position } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';
import ChangeCircleIcon from '@mui/icons-material/ChangeCircle';
import CottageIcon from '@mui/icons-material/Cottage';
import SolarPowerIcon from '@mui/icons-material/SolarPower';

import { Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../../api/endpoints';
import { updateValue, useWs } from '../../utils';

import { NodeState } from '../types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "PvNodeState";

const PvNode = ({ data, isConnectable }:any) => {
  const WS = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);
  const updateFormValue = updateValue(WS.updateData);
  return (
    <>
    <Grid container spacing={0} style={{alignContent: "center"}}>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 10 }}>PV</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}} color={WS.data?.node_color}>
            <SolarPowerIcon sx={{ fontSize: 35 }}  />
        </Grid>
      </Grid>
      {false &&
        <Handle
        type="source"
        position={Position.Top}
        id="a"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />}
      
      <Handle
        type="source"
        position={Position.Bottom}
        id="b"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
    </>
  );
};

export default PvNode;
