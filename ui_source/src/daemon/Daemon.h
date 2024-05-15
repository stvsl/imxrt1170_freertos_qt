#ifndef __DAEMON_H__
#define __DAEMON_H__
#include <qul/eventqueue.h>
#include <qul/property.h>
#include <qul/singleton.h>

///////////////////////////////////////////////////////////
/// @brief Daemon
///
class Daemon : public Qul::Singleton<Daemon>, public Qul::EventQueue<bool> {
  void onEvent(const bool &value) { (void)value; }

public:
  Daemon();

  enum EventType {
    LED_STATUS_CHANGED,
    COUNT,
  };

  Qul::Property<int> led_status;

  void pushEvent(int event, int value);
};

#endif // __DAEMON_H__
