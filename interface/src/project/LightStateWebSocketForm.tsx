import { FC } from 'react';

import { Switch } from '@mui/material';

import { WEB_SOCKET_ROOT } from '../api/endpoints';
import { BlockFormControlLabel, FormLoader, MessageBox, SectionContent } from '../components';
import { updateValue, useWs } from '../utils';

import { LightState, NodeState } from './types';

export const NODE_SETTINGS_WEBSOCKET_URL = WEB_SOCKET_ROOT + "nodeState";

const LightStateWebSocketForm: FC = () => {
  const { connected, updateData, data } = useWs<NodeState>(NODE_SETTINGS_WEBSOCKET_URL);

  const updateFormValue = updateValue(updateData);

  const content = () => {
    if (!connected || !data) {
      return (<FormLoader message="Connecting to WebSocket…" />);
    }
    return (
      <>
        <MessageBox
          level="info"
          message="The switch below controls the LED via the WebSocket. It will automatically update whenever the LED state changes."
          my={2}
        />
        <BlockFormControlLabel
          control={
            <Switch
              name="node_status"
              checked={data.node_status}
              onChange={updateFormValue}
              color="primary"
            />
          }
          label="LED State?"
        />
      </>
    );
  };

  return (
    <SectionContent title='WebSocket Example' titleGutter>
      {content()}
    </SectionContent>
  );
};

export default LightStateWebSocketForm;
