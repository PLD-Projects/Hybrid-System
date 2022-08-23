import React from "react";

import { Handle, Position } from 'react-flow-renderer';

import ChangeCircleIcon from '@mui/icons-material/ChangeCircle';

import {Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../../api/endpoints';
import { updateValue, useWs } from '../../utils';

import { NodeState } from '../types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "TsNodeState";

const TsNode = ({ data, isConnectable }:any) => {
  const WS = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);
  const updateFormValue = updateValue(WS.updateData);
  return (
    <>
    <Grid container spacing={0} style={{alignContent: "center"}}>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 10 }}>Transfer Switch</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}} color={WS.data?.node_color}>
            <ChangeCircleIcon sx={{ fontSize: 35 }}  />
        </Grid>
      </Grid>
      <Handle
        type="target"
        position={Position.Left}
        id="a"
        isConnectable={isConnectable}
      />
      <Handle
        type="target"
        position={Position.Bottom}
        id="b"
        isConnectable={isConnectable}
      />
      <Handle
        type="source"
        position={Position.Right}
        id="c"
        isConnectable={isConnectable}
      />
    </>
  );
};

export default TsNode;
