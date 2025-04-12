#include "engine.h"

#include "event.h"
#include "log.h"

namespace Sparkle {

Engine::Engine() {
  // Constructor implementation
}

Engine::~Engine() {
  // Destructor implementation
}

bool test(Event& e){
  SPRK_INFO("dispatch {}", e.toString());
  return true;
}

void Engine::Run() {
  KeyPressedEvent e(65, false);

  EventDispatcher dis(e);
  dis.dispatch<KeyPressedEvent>(test);
}
} // namespace Sparkle
