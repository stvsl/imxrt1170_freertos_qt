#include <MCUDemo.h>

#include <qul/application.h>
#include <qul/qul.h>
#include <qul/rootitem.h>

#include <platforminterface/log.h>

#include <FreeRTOS.h>
#include <string.h>
#include <string>
#include <task.h>

#include <board.h>

static void Qul_Thread(void *argument);

int main() {
  Qul::initHardware();
  Qul::initPlatform();
  if (xTaskCreate(Qul_Thread, "Qul_Thread", 32768, 0, 4, 0) != pdPASS) {
    Qul::PlatformInterface::log("Task creation failed!.\r\n");
    configASSERT(false);
  }

  vTaskStartScheduler();

  // Should not reach this point
  return 1;
}

static void Qul_Thread(void *argument) {
  (void)argument;
  Qul::Application _qul_app;
  static struct ::MCUDemo _qul_item;
  _qul_app.setRootItem(&_qul_item);
#ifdef APP_DEFAULT_UILANGUAGE
  _qul_app.settings().uiLanguage.setValue(APP_DEFAULT_UILANGUAGE);
#endif
  // _qul_app.exec();
  while (true) {
    _qul_app.update();
    vTaskDelay(10);
  }
}

extern "C" {
void vApplicationStackOverflowHook(TaskHandle_t xTask,
                                   signed char *pcTaskName) {
  (void)xTask;
  (void)pcTaskName;

  Qul::PlatformInterface::log("vApplicationStackOverflowHook");
  configASSERT(false);
}

void vApplicationMallocFailedHook(void) {
  Qul::PlatformInterface::log("vApplicationMallocFailedHook");
  configASSERT(false);
}
}