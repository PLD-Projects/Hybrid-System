import React from 'react';

import { Handle, Position } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';
import ChangeCircleIcon from '@mui/icons-material/ChangeCircle';
import CottageIcon from '@mui/icons-material/Cottage';

import { Typography,Grid,FormControlLabel,Switch} from '@mui/material';

const LoadNode = ({ data, isConnectable }:any) => {
  return (
    <>
    <Grid container spacing={0} style={{alignContent: "center"}}>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 10 }}>Load</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <CottageIcon sx={{ fontSize: 35 }}  />
        </Grid>
      </Grid>
      <Handle
        type="target"
        position={Position.Right}
        id="a"
        isConnectable={isConnectable}
        style={{ background: 'transparent', top:30 }}
      />
      <Handle
        type="target"
        position={Position.Bottom}
        id="b"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
    </>
  );
};

export default LoadNode;
