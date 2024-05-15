#include "AppBredge.h"
#include "src/daemon/Daemon.h"
#include <cstdint>

AppBredge::AppBredge() {
  subscribe(App::LED_STATUS_CHANGED,
            std::function<void(uint8_t)>(app_base_set_led_status));
}

void app_base_set_led_status(const uint8_t data) {
  Daemon::instance().led_status.setValue(data);
  Daemon::instance().postEvent(true);
}
