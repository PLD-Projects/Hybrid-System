export interface LightState {
  led_on: boolean;
}

export interface NodeState {
  node_color : string;
  node_val : Number;
  node_status: boolean;
}

export interface LightMqttSettings {
  unique_id: string;
  name: string;
  mqtt_path: string;
}
