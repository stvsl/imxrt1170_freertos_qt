/******************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Quick Ultralite module.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
******************************************************************************/
#include "board.h"
#include "platform_os.h"

uint8_t ledstatus = 1;
uint32_t tick = 0;

void SysTick_Handler() {
  systick();
#if 0
  if (tick == 500) {
    if (ledstatus == 1) {
      USER_LED_ON();
      ledstatus = 0;
    } else {
      USER_LED_OFF();
      ledstatus = 1;
    }
    tick = 0;
  } else {
    tick++;
  }
#endif
}

// Force linker to add this file, including SysTick_Handler, to the binary.
// When linkedn the linker finds the strong symbol and links successfully to
// our SysTick_Handler implementation.
int sys_clock_c;
