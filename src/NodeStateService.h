#ifndef NodeStateService_h
#define NodeStateService_h

#include <WebSocketTxRx.h>

#define LED_PIN 2

#define DEFAULT_LED_STATE false
#define OFF_STATE "OFF"
#define ON_STATE "ON"

// Note that the built-in LED is on when the pin is low on most NodeMCU boards.
// This is because the anode is tied to VCC and the cathode to the GPIO 4 (Arduino pin 2).
#ifdef ESP32
#define LED_ON 0x1
#define LED_OFF 0x0
#elif defined(ESP8266)
#define LED_ON 0x0
#define LED_OFF 0x1
#endif



class NodeState {
 public:
  String Color;
  float val;
  bool status;

  static void read(NodeState& settings, JsonObject& root) {
    root["node_color"] = settings.Color;
    root["node_val"] = settings.val;
    root["node_status"] = settings.status;
  }

  static StateUpdateResult update(JsonObject& root, NodeState& settings) {
    if(root.containsKey("node_color"))settings.Color = root["node_color"].as<String>();
    if(root.containsKey("node_val"))settings.val = root["node_val"];
    if(root.containsKey("node_status"))settings.status = root["node_status"];
    return StateUpdateResult::CHANGED;
  }

};

class NodeStateService : public StatefulService<NodeState> {
 public:
  NodeStateService(AsyncWebServer* server,
                    SecurityManager* securityManager, const char* webSocketPath, int pin = 0);
  void begin();

 private:
  WebSocketTxRx<NodeState> _webSocket;
  int pinNum = 0;
  void registerConfig();
  void onConfigUpdated();
};

#endif
