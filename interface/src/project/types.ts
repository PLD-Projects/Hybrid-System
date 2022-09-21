export interface LightState {
  led_on: boolean;
}

export interface NodeState {
  node_color : string;
  node_val : Number;
  node_status: boolean;
}

export interface EdgeState {
  p2gi: boolean;
  p2i: boolean;
  gi2g: boolean;
  g2l: boolean;
  g2i: boolean;
  i2l: boolean;
  i2b: boolean;
  b2i: boolean;
}

export interface LightMqttSettings {
  unique_id: string;
  name: string;
  mqtt_path: string;
}
