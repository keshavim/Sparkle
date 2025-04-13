#pragma once

#include "sprkpch.h"
#include "core.h"
#include "event.h"



namespace Sparkle {


class Window{
public:

  using EventCallbackFn = std::function<void(Event&)>;
  virtual ~Window() {}

  virtual void onUpdate() = 0;
  virtual u32 getWidth() const = 0;
  virtual u32 getHeight() const = 0;

  virtual void setEventCallback(const EventCallbackFn& callback) = 0;
  virtual void setVsync(bool enabled) = 0;
  virtual bool isVsync() const = 0;


  static Window* create(const char* name = "title",const u32 width = 1280, const u32 height = 720);
};

}
