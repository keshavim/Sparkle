#include "sprkpch.h"

#include "engine.h"

#include "event.h"
#include "log.h"

namespace Sparkle {

Engine::Engine() {
m_window = std::unique_ptr<Window>(Window::create()); 
}

Engine::~Engine() {
  // Destructor implementation
}

bool test(Event &e) {
  SPRK_INFO("dispatch {}", e.toString());
  return true;
}

void Engine::Run() {

  while(m_window){
 m_window->onUpdate(); 
  }

}

} // namespace Sparkle
