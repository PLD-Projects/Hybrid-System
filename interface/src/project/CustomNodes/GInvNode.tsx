import React from "react";

import { Handle, Position } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';

import {Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../../api/endpoints';
import { updateValue, useWs } from '../../utils';

import { NodeState } from '../types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "InvNodeState";

const GInvNode = ({ data, isConnectable }:any) => {
  const WS = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);

  const updateFormValue = updateValue(WS.updateData);
  return (
    <>
      <Grid container spacing={0} style={{alignContent: "center"}}>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 8 }}>On-Grid Inverter</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}} sx={{ border: 1, fontSize:30 }} color={WS.data?.node_color}>
            <ElectricalServicesIcon sx={{ fontSize: 20 }}  />|<PowerInputIcon sx={{ fontSize: 20 }} />
        </Grid>
      </Grid>
      {false &&
        <Handle
        type="target"
        position={Position.Left}
        id="a"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
      }
      
      <Handle
        type="source"
        position={Position.Right}
        id="b"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
    </>
  );
};

export default GInvNode;
