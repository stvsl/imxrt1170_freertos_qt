#include "Daemon.h"

#if defined(IS_LOCAL_DEBIG)
#include "src/core/debug_symbol.h"
#else
#include "board.h"
#endif

Daemon::Daemon() {}

void Daemon::pushEvent(int type, int value) {
#if defined(IS_LOCAL_DEBIG)
  // LOG_PRINT("push Event:", type, value);
#else
  // Qul::PlatformInterface::log("pushEvent:", (int)type, (int)value);
  if (value) {
    // USER_LED_ON();
  } else {
    // USER_LED_OFF();
  }
#endif
}