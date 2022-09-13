import React, { memo } from 'react';

import { Handle, Position } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';
import ChangeCircleIcon from '@mui/icons-material/ChangeCircle';
import CottageIcon from '@mui/icons-material/Cottage';
import SolarPowerIcon from '@mui/icons-material/SolarPower';

import { Typography,Grid,FormControlLabel,Switch} from '@mui/material';

const PvNode = ({ data, isConnectable }:any) => {
  return (
    <>
    <Grid container spacing={0} style={{alignContent: "center"}}>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 10 }}>PV</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <SolarPowerIcon sx={{ fontSize: 35 }}  />
        </Grid>
      </Grid>
      <Handle
        type="source"
        position={Position.Top}
        id="a"
        isConnectable={isConnectable}
        style={{ background: 'transparent' }}
      />
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
