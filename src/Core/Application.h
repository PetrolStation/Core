#pragma once

#include <type_traits>

struct CApplication {
  void (*newLib)();
  void (*start)();
  void (*update)();
  void (*finish)();
  void (*deleteLib)();
};

//extern "C" {
//  CApplication getApplication(){ return __FUNCSS; }
//}

class Application {
public:
  virtual void start() = 0;
  virtual void update() = 0;
  virtual void finish() = 0;

  template <typename T, T** ob> static CApplication getApplicationF() {
    if constexpr (std::is_base_of_v<Application, T>){
    return {newApplication<T, ob>, startApplication<T, ob>,
               updateApplication<T, ob>, finishApplication<T, ob>,
               deleteApplication<T, ob>};
    }
    return {nullptr, nullptr, nullptr, nullptr, nullptr};
  }

private:
  template <typename T, T** ob> static void newApplication() {
    *ob = new T();
  }
  template <typename T, T** ob> static void startApplication() {
    ((T*)*ob)->start();
  }
  template <typename T, T** ob> static void updateApplication() {
    ((T*)*ob)->update();
  }
  template <typename T, T** ob> static void finishApplication() {
    ((T*)*ob)->finish();
  }
  template <typename T, T** ob> static void deleteApplication() {
    delete ((T*)*ob);
  }
};

#define EXPORT_APPLICATION(appClass) appClass* appObject = nullptr; extern "C" { \
  CApplication getApplication(); \
} \
CApplication getApplication() { return Application::getApplicationF<appClass, &appObject>(); }
//Application::setApplication<Application>()
