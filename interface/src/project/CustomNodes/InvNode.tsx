import React from "react";

import { Handle, Position } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';

import {Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../../api/endpoints';
import { updateValue, useWs } from '../../utils';

import { NodeState } from '../types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "InvNodeState";

const InvNode = ({ data, isConnectable }:any) => {
  const WS = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);
  const updateFormValue = updateValue(WS.updateData);
  return (
    <>
    <Grid container spacing={0} style={{alignContent: "center"}}>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 9}}>Off-Grid Inverter</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}} sx={{ border: 1, fontSize:30 }} color={WS.data?.node_color}>
            <ElectricalServicesIcon sx={{ fontSize: 20 }}  />|<PowerInputIcon sx={{ fontSize: 20 }} />
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <FormControlLabel 
            control={
            <Switch 
              name="node_status"
              checked={WS.data?.node_status}
              onChange={updateFormValue}
              color="primary"
              size='small'
             />
             } 
             label={<Typography  sx={{ fontSize: 10 }} align='center'>{WS.data?.node_val.toFixed(0).toString()}V</Typography>} 
             labelPlacement='bottom' />
        </Grid>
      </Grid>
      <Handle
        type="target"
        position={Position.Left}
        id="a"
        isConnectable={isConnectable}
        style={{ background: 'transparent', top: 35 }}
      />
      <Handle
        type="source"
        position={Position.Top}
        id="b"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
      <Handle
        type="target"
        position={Position.Right}
        id="c"
        isConnectable={isConnectable}
        style={{ background: 'transparent', top: 35 }}
      />
      <Handle
        type="source"
        position={Position.Bottom}
        id="d"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
      <Handle
        type="target"
        position={Position.Bottom}
        id="e"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
    </>
  );
};

export default InvNode;
