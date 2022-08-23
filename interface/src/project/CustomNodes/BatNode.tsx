import React from "react";

import { Handle, Position } from 'react-flow-renderer';

import BatteryChargingFullIcon from '@mui/icons-material/BatteryChargingFull';

import {Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../../api/endpoints';
import { updateValue, useWs } from '../../utils';

import { NodeState } from '../types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "BatNodeState";

const BatNode = ({ data, isConnectable }:any) => {
  const WS = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);
  const updateFormValue = updateValue(WS.updateData);

  return (
    <>
    <Grid container spacing={0} >
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 10 }}>Battery</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}} color={WS.data?.node_color}>
            <BatteryChargingFullIcon sx={{ fontSize: 40 }}  />
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}}>
        <Typography  sx={{ fontSize: 10 }} align='center'>{WS.data?.node_val.toString()}V</Typography>
        </Grid>
      </Grid>
      <Handle
        type="target"
        position={Position.Top}
        id="a"
        isConnectable={isConnectable}
      />
      <Handle
        type="source"
        position={Position.Right}
        id="b"
        isConnectable={isConnectable}
      />
    </>
  );
};

export default BatNode;