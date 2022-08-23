#include <NodeStateService.h>

NodeStateService::NodeStateService(AsyncWebServer* server,
                                    SecurityManager* securityManager, const char* webSocketPath) :
    _webSocket(NodeState::read,
               NodeState::update,
               this,
               server,
               webSocketPath,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  // configure led to be output
  pinMode(LED_PIN, OUTPUT);

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
  // digitalWrite(LED_PIN, _state.ledOn ? LED_ON : LED_OFF);
}

