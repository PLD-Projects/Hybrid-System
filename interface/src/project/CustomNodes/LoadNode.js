import React, { memo } from 'react';

import { Handle } from 'react-flow-renderer';

import ElectricalServicesIcon from '@mui/icons-material/ElectricalServices';
import PowerInputIcon from '@mui/icons-material/PowerInput';
import ChangeCircleIcon from '@mui/icons-material/ChangeCircle';
import CottageIcon from '@mui/icons-material/Cottage';

import { Typography,Grid,FormControlLabel,Switch} from '@mui/material';

export default memo(({ data, isConnectable }) => {
  return (
    <>

    <Grid container spacing={0} align="center">
        <Grid item xs={12} style={{textAlign: "center"}}>
            <Typography align='center' sx={{ fontSize: 10 }}>Load</Typography>
        </Grid>
        <Grid item xs={12} style={{textAlign: "center"}}>
            <CottageIcon sx={{ fontSize: 35 }}  />
        </Grid>
      </Grid>
      <Handle
        type="target"
        position="left"
        id="a"
        style={{ top: 40}}
        isConnectable={isConnectable}
      />
    </>
  );
});
