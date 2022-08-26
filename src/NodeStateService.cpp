#include <NodeStateService.h>

NodeStateService::NodeStateService(AsyncWebServer* server,
                                    SecurityManager* securityManager, const char* webSocketPath, int pin) :
    _webSocket(NodeState::read,
               NodeState::update,
               this,
               server,
               webSocketPath,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  // configure led to be output
  pinNum = pin;
  if(pinNum > 0)pinMode(pinNum, OUTPUT);

  // configure settings service update handler to update LED state
  addUpdateHandler([&](const String& originId) { onConfigUpdated(); }, false);
  
}

void NodeStateService::begin() {
  _state.Color = "grey";
  _state.val = 0;
  _state.status = false;
  onConfigUpdated();
}

void NodeStateService::onConfigUpdated() {
  if(pinNum > 0)digitalWrite(pinNum, _state.status ? LED_ON : LED_OFF);
}

