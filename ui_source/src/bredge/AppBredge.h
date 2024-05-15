#ifndef __APP_BREDGE_H__
#define __APP_BREDGE_H__
#include <cstdint>
#include <platforminterface/allocator.h>
#include <qul/eventqueue.h>
#include <qul/property.h>
#include <qul/singleton.h>
namespace App {
enum EventType {
  LED_STATUS_CHANGED,
  COUNT,
};
}
///////////////////////////////////////////////////////////
/// @brief AppBredge
///
struct AppBredge : public Qul::Singleton<AppBredge>,
                   public Qul::EventQueue<bool> {
  void onEvent(const bool &event) override{};

public:
  template <typename... Args>
  void subscribe(const App::EventType event,
                 const std::function<void(Args...)> &callback) {
    // 判断参数类型是不是uint8_t
    listeners[event].emplace_back(callback);
  }

  template <typename... Args>
  void publish(const App::EventType event, Args &&...args) {
    if (listeners.find(event) != listeners.end()) {
      for (const auto &callback : listeners[event]) {
        callback(std::forward<Args>(args)...);
      }
    }
  }

  Qul::PlatformInterface::Map<App::EventType, Qul::PlatformInterface::Vector<
                                                  std::function<void(uint8_t)>>>
      listeners;

  AppBredge();
};

template <typename... Args>
void app_event_push(App::EventType event, Args... args) {
  AppBredge::instance().publish(event, args...);
}

// 线程安全的原子操作
void app_base_set_led_status(const uint8_t data);

#endif // __APP_BREDGE_H__
