#include "Sparkle.h"
#include "stdio.h"

class Application : public Sparkle::Engine {
public:
  Application() { printf("createted\n"); }
  ~Application() override { printf("deleted"); }

};

Sparkle::Engine *Sparkle::createApplication(){
  return new Application();
}

