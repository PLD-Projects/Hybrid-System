#include <Arduino.h>
#include <ESP8266React.h>
#include <NodeStateService.h>
#include <EdgeStateService.h>
#include <AdcService.h>
#include <PinMapping.h>
// #include "ZMPT101B.h"

#define SERIAL_BAUD_RATE 115200

#define PV_NODE_SOCKET_PATH "/ws/PvNodeState"
#define GRID_NODE_SOCKET_PATH "/ws/GridNodeState"
#define GINV_NODE_SOCKET_PATH "/ws/GInvNodeState"
#define INV_NODE_SOCKET_PATH "/ws/InvNodeState"
#define BAT_NODE_SOCKET_PATH "/ws/BatNodeState"
#define LOAD_NODE_SOCKET_PATH "/ws/LoadNodeState"
#define EDGE_SOCKET_PATH "/ws/EdgeState"

// ws://localhost:3000/ws/nodeState?access_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6ImFkbWluIiwiYWRtaW4iOnRydWV9.-oSCJXsk-RXgdeojzpH9O85GzBbuaSNUvc1ofx6-myA
AsyncWebServer server(80);
ESP8266React esp8266React(&server);

NodeStateService pvNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),PV_NODE_SOCKET_PATH);
NodeStateService gridNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),GRID_NODE_SOCKET_PATH,CHG_RLY);
NodeStateService ginvNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),GINV_NODE_SOCKET_PATH);
NodeStateService invNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),INV_NODE_SOCKET_PATH,INV_RLY);
NodeStateService batNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),BAT_NODE_SOCKET_PATH);
NodeStateService loadNodeStateService = NodeStateService(&server,esp8266React.getSecurityManager(),LOAD_NODE_SOCKET_PATH);
EdgeStateService EdgesStateService = EdgeStateService(&server,esp8266React.getSecurityManager(),EDGE_SOCKET_PATH);

unsigned long last_millis = 0;
// ZMPT101B voltageSensor(36);
AdcService ADC = AdcService();

void setup() {
  // start serial and filesystem
  Serial.begin(SERIAL_BAUD_RATE);
  pinMode(WIFI_LED,OUTPUT);
  

  // start the framework and demo project
  esp8266React.begin();

  pvNodeStateService.begin();
  gridNodeStateService.begin();
  ginvNodeStateService.begin();
  invNodeStateService.begin();
  batNodeStateService.begin();
  loadNodeStateService.begin();

  // start the server
  server.begin();

  ADC.initService();
  ADC.sentivity_grid = 0.43733;
  ADC.sentivity_inv = 0.437333;
  ADC.sentivity_bat = 1;//0.0163;
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
    
    // pvNodeStateService
    if(digitalRead(PV_PIN))doc["node_color"] = "green";
    else doc["node_color"] = "grey";
    JsonObject jsonObject = doc.as<JsonObject>();
    pvNodeStateService.update(jsonObject,NodeState::update,"loop");
    // doc["node_status"] = status;
    // status = !status;
    // val++;
    // if(colour == "grey")colour = "#ffcc00";
    // else if(colour == "#ffcc00")colour = "red";
    // else if(colour == "red")colour = "grey";
    

    // doc["node_val"] = ceil(ADC.read_grid);
    // JsonObject jsonObject = doc.as<JsonObject>();
    // gridNodeStateService.update(jsonObject,NodeState::update,"loop");

    // doc["node_val"] = ADC.read_bat; //String(ADC.read_bat);
    // jsonObject = doc.as<JsonObject>();
    // batNodeStateService.update(jsonObject,NodeState::update,"loop");

    
    // invNodeStateService.updateStatus();
    // doc["node_val"] = ceil(ADC.read_inv);
    // jsonObject = doc.as<JsonObject>();
    // invNodeStateService.update(jsonObject,NodeState::update,"loop");


    // loadNodeStateService.update(jsonObject,NodeState::update,"loop");
    // tsNodeStateService.update(jsonObject,NodeState::update,"loop");
  }
}
