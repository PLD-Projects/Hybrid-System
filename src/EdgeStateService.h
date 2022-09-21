#ifndef EdgeStateService_h
#define EdgeStateService_h

#include <WebSocketTxRx.h>

class EdgeState {
 public:
  bool p2gi;
  bool p2i;
  bool gi2g;
  bool g2l;
  bool g2i;
  bool i2l;
  bool i2b;
  bool b2i;

  static void read(EdgeState& settings, JsonObject& root) {
    root["p2gi"] = settings.p2gi;
    root["p2i"] = settings.p2i;
    root["gi2g"] = settings.gi2g;
    root["g2l"] = settings.g2l;
    root["g2i"] = settings.g2i;
    root["i2l"] = settings.i2l;
    root["i2b"] = settings.i2b;
    root["b2i"] = settings.b2i;
  }

  static StateUpdateResult update(JsonObject& root, EdgeState& settings) {
    if(root.containsKey("p2gi"))settings.p2gi = root["p2gi"];
    if(root.containsKey("p2i"))settings.p2i = root["p2i"];
    if(root.containsKey("gi2g"))settings.gi2g = root["gi2g"];
    if(root.containsKey("g2l"))settings.g2l = root["g2l"];
    if(root.containsKey("g2i"))settings.g2i = root["g2i"];
    if(root.containsKey("i2l"))settings.i2l = root["i2l"];
    if(root.containsKey("i2b"))settings.i2b = root["i2b"];
    if(root.containsKey("b2i"))settings.b2i = root["b2i"];
    return StateUpdateResult::CHANGED;
  }

};

class EdgeStateService : public StatefulService<EdgeState> {
 public:
  EdgeStateService(AsyncWebServer* server,
                    SecurityManager* securityManager, const char* webSocketPath);
  void begin();

 private:
  WebSocketTxRx<EdgeState> _webSocket;
};

#endif
