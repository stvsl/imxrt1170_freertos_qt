/******************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
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
#include <platform/private/mem-freertos.h>
#include <platform/private/mem_info.h>

#include <platforminterface/log.h>

#include <FreeRTOS.h>
#include <portable.h>
#include <portmacro.h>
#include <task.h>

#include <string.h>
#include <algorithm>

#define ALIGNED_SIZE_RESERVATION std::max(1U, portBYTE_ALIGNMENT / sizeof(size_t))

namespace Qul {
namespace Platform {
namespace Private {
namespace FreeRtos {

void printHeapStats(void)
{
    PlatformInterface::log("\r\n"
                           "FreeHeapSize: %d\r\n"
                           "MinimumEverFreeHeapSize: %d\r\n",
                           xPortGetFreeHeapSize(),
                           xPortGetMinimumEverFreeHeapSize());
}

void printStackStats(void)
{
    PlatformInterface::log("Stack: %llu (peak)\r\n", Private::maxStackUsage());
}

void *allocate(std::size_t size)
{
    void *ptr = pvPortMalloc(sizeof(size_t) * ALIGNED_SIZE_RESERVATION + size);

    if (ptr == NULL) {
        return ptr;
    }

    *((size_t *) ptr) = size;

    return (size_t *) ptr + ALIGNED_SIZE_RESERVATION;
}

void deallocate(void *ptr)
{
    if (ptr != NULL) {
        vPortFree((size_t *) ptr - ALIGNED_SIZE_RESERVATION);
    }
}

void *reallocate(void *ptr, size_t s)
{
    if (ptr == NULL) {
        return allocate(s);
    }

    size_t oldSize = *((size_t *) ptr - ALIGNED_SIZE_RESERVATION);

    if (s == oldSize) {
        return ptr;
    }

    void *newPtr = NULL;

    if (s > 0) {
        newPtr = allocate(s);
        memcpy(newPtr, ptr, (s > oldSize) ? oldSize : s);
    }

    deallocate(ptr);

    return newPtr;
}

size_t allocationSize(void *ptr)
{
    if (!ptr)
        return 0;

    return *((size_t *) ptr - ALIGNED_SIZE_RESERVATION);
}

} // namespace FreeRtos
} // namespace Private
} // namespace Platform
} // namespace Qul
