#include <Arduino.h>
#include <ESP8266React.h>
#include <NodeStateService.h>
#include "ZMPT101B.h"
#include <AdcService.h>

#define SERIAL_BAUD_RATE 115200

#define GRID_NODE_SOCKET_PATH "/ws/GridNodeState"
#define BAT_NODE_SOCKET_PATH "/ws/BatNodeState"
#define INV_NODE_SOCKET_PATH "/ws/InvNodeState"
#define LOAD_NODE_SOCKET_PATH "/ws/LoadNodeState"
#define TS_NODE_SOCKET_PATH "/ws/TsNodeState"

// ws://localhost:3000/ws/nodeState?access_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFkbWluIiwiYWRtaW4iOnRydWV9.-oSCJXsk-RXgdeojzpH9O85GzBbuaSNUvc1ofx6-myA
AsyncWebServer server(80);
ESP8266React esp8266React(&server);

NodeStateService gridNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),GRID_NODE_SOCKET_PATH);
NodeStateService batNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),BAT_NODE_SOCKET_PATH);
NodeStateService invNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),INV_NODE_SOCKET_PATH);
NodeStateService loadNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),LOAD_NODE_SOCKET_PATH);
NodeStateService tsNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),TS_NODE_SOCKET_PATH);

unsigned long last_millis = 0;
// ZMPT101B voltageSensor(36);
AdcService ADC = AdcService();

void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);

  // start the framework and demo project
  esp8266React.begin();

  gridNodeStateService.begin();
  batNodeStateService.begin();
  invNodeStateService.begin();
  loadNodeStateService.begin();
  tsNodeStateService.begin();

  // start the server
  server.begin();
  Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
  delay(100);
  ADC.calibrate();
  ADC.sentivity_grid = 0.35;
  ADC.sentivity_inv = 0.35;
  ADC.sentivity_bat = 0.0163;
  // Serial.println(voltageSensor.calibrate());
  // voltageSensor.setSensitivity(0.35);
//  currentSensor.calibrate();
  Serial.println("Done!");
  ADC.startService();
}

bool status = false;
int val = 0;
String colour = "grey";

void loop() {
  // run the framework's loop function
  esp8266React.loop();
  // float U = voltageSensor.getVoltageAC();
  if(millis()-last_millis > 5000){
    last_millis = millis();
    DynamicJsonDocument doc(2048);

    doc["node_color"] = colour;
    doc["node_status"] = status;
    status = !status;
    val++;
    if(colour == "grey")colour = "#ffcc00";
    else if(colour == "#ffcc00")colour = "red";
    else if(colour == "red")colour = "grey";
    

    doc["node_val"] = ADC.read_grid;
    JsonObject jsonObject = doc.as<JsonObject>();
    gridNodeStateService.update(jsonObject,NodeState::update,"loop");

    doc["node_val"] = ADC.read_bat;
    jsonObject = doc.as<JsonObject>();
    batNodeStateService.update(jsonObject,NodeState::update,"loop");

    doc["node_val"] = ADC.read_inv;
    jsonObject = doc.as<JsonObject>();
    invNodeStateService.update(jsonObject,NodeState::update,"loop");


    loadNodeStateService.update(jsonObject,NodeState::update,"loop");
    tsNodeStateService.update(jsonObject,NodeState::update,"loop");
  }
}
