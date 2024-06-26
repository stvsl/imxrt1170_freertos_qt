#include <MCUCluser.h>

#include <qul/application.h>
#include <qul/qul.h>
#include <qul/rootitem.h>

#include <platforminterface/log.h>

#include <FreeRTOS.h>
#include <string>
#include <task.h>

#include "bredge/messager.h"
#include <board.h>

static void Qul_Thread(void *argument);
static void TestApp_Thread(void *argument);

int main() {
  Qul::initHardware();
  Qul::initPlatform();
  if (xTaskCreate(Qul_Thread, "Qul_Thread", 32768, 0, 4, 0) != pdPASS) {
    Qul::PlatformInterface::log("Task creation failed!.\r\n");
    configASSERT(false);
  }

  if (xTaskCreate(TestApp_Thread, "TestApp_Thread", 4096, 0, 3, 0) != pdPASS) {
    Qul::PlatformInterface::log("Task creation failed!.\r\n");
    configASSERT(false);
  };
  vTaskStartScheduler();

  // Should not reach this point
  return 1;
}
static void TestApp_Thread(void *argument) {
  static uint8_t i = 0;
  while (true) {
    i++;
    Msg_SendToUI(Message::GEAR, i);
    vTaskDelay(500);
  }
}
static void Qul_Thread(void *argument) {
  (void)argument;
  Qul::Application _qul_app;
  static struct ::MCUCluser _qul_item;
  _qul_app.setRootItem(&_qul_item);
#ifdef APP_DEFAULT_UILANGUAGE
  _qul_app.settings().uiLanguage.setValue(APP_DEFAULT_UILANGUAGE);
#endif
  _qul_app.exec();
  // while (true) {
  //   _qul_app.update();
  //   vTaskDelay(10);
  // }
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