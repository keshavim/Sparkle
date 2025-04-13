#pragma once

#include "Core/window.h"
#include "GLFW/glfw3.h"

namespace Sparkle {


class LinuxWindow : public Window{
public:

  LinuxWindow(const char* name, const u32 width, const u32 height);
  ~LinuxWindow();

  void onUpdate() override;
  inline u32 getWidth() const override {return m_data.width;}
  inline u32 getHeight() const override {return m_data.height;}

  inline void setEventCallback(const EventCallbackFn& callback) override {m_data.callback = callback;}
  void setVsync(bool enabled) override;
  bool isVsync() const override {return m_data.vsync;};


private:
    virtual void init(const char* name = "title", const u32 width = 1280, const u32 height = 720);
    virtual void shutdown();
private:
  GLFWwindow* m_handle;

  struct Data{
    std::string title;
    u32 width, height;
    bool vsync;
  
    EventCallbackFn callback;

  }m_data;


};

}
