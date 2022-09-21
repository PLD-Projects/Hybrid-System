#include <EdgeStateService.h>

EdgeStateService::EdgeStateService(AsyncWebServer* server,
                                    SecurityManager* securityManager, const char* webSocketPath):
    _webSocket(EdgeState::read,
               EdgeState::update,
               this,
               server,
               webSocketPath,
               securityManager,
               AuthenticationPredicates::IS_AUTHENTICATED) {
  
}

void EdgeStateService::begin() {
  _state.p2gi=false;
  _state.p2i=false;
  _state.gi2g=false;
  _state.g2l=false;
  _state.g2i=false;
  _state.i2l=false;
  _state.i2b=false;
  _state.b2i=false;
}


