import React from "react";

import { Handle, Position } from 'react-flow-renderer';

import BoltIcon from '@mui/icons-material/Bolt';

import {Typography,Grid,FormControlLabel,Switch} from '@mui/material';

import { WEB_SOCKET_ROOT } from '../../api/endpoints';
import { updateValue, useWs } from '../../utils';

import { NodeState } from '../types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "GridNodeState";

const GridNode = ({ data, isConnectable }:any) => {
  const WS = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);

  const updateFormValue = updateValue(WS.updateData);

  return (
    <>
      <Grid container spacing={0}>
        <Grid item xs={12} style={{textAlign: "center"}}>
          <Typography align='center' sx={{ fontSize: 10 }}>Grid</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}} color={WS.data?.node_color}>
          <BoltIcon sx={{ fontSize: 40 }}  />
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}}>
          <Typography align='center' sx={{ fontSize: 10 }}>{WS.data?.node_val.toString()} V</Typography>
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
            label={<Typography  sx={{ fontSize: 10 }} align='center'>Charger</Typography>}
            labelPlacement='bottom'
          />
        </Grid>
      </Grid>
      <Handle
         type="source"
         position={Position.Bottom}
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

export default GridNode;
