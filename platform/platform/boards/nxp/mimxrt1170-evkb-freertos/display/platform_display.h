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
#pragma once

#include <platforminterface/screen.h>

#include "fsl_dc_fb.h"
#include "fsl_mipi_dsi.h"

#include "platform_config.h"

/* Where the frame buffer is shown in the screen. */
#define DEMO_BUFFER_START_X 0U
#define DEMO_BUFFER_START_Y 0U

#define DEMO_LCDIFV2 LCDIFV2
#define DEMO_LCDIFV2_IRQn LCDIFv2_IRQn
#define DEMO_LCDIFV2_IRQHandler LCDIFv2_IRQHandler

#define DEMO_DISPLAY_CONTROLLER_ELCDIF 0
#define DEMO_DISPLAY_CONTROLLER_LCDIFV2 1

#if (USE_MIPI_PANEL == MIPI_PANEL_RK055AHD091)
#define DEMO_PANEL_HEIGHT 1280
#define DEMO_PANEL_WIDTH 720
#define DEMO_HSW 8
#define DEMO_HFP 32
#define DEMO_HBP 32
#define DEMO_VSW 2
#define DEMO_VFP 16
#define DEMO_VBP 14
#elif (USE_MIPI_PANEL == MIPI_PANEL_RK055MHD091)
#define DEMO_PANEL_HEIGHT 1280
#define DEMO_PANEL_WIDTH 720
#define DEMO_HSW 6
#define DEMO_HFP 12
#define DEMO_HBP 24
#define DEMO_VSW 2
#define DEMO_VFP 16
#define DEMO_VBP 14
#else
#define DEMO_PANEL_HEIGHT 960
#define DEMO_PANEL_WIDTH 540
#define DEMO_HSW 2
#define DEMO_HFP 32
#define DEMO_HBP 30
#define DEMO_VSW 2
#define DEMO_VFP 16
#define DEMO_VBP 14
#endif
#define DEMO_POL_FLAGS \
    (kLCDIFV2_DataEnableActiveHigh | kLCDIFV2_VsyncActiveLow | kLCDIFV2_HsyncActiveLow \
     | kLCDIFV2_DriveDataOnFallingClkEdge)

#define DEMO_PANEL_RK055AHD091 MIPI_PANEL_RK055AHD091
#define DEMO_PANEL_RK055IQH091 MIPI_PANEL_RK055IQH091
#define DEMO_PANEL_RK055MHD091 MIPI_PANEL_RK055MHD091

#ifndef DEMO_PANEL
#define DEMO_PANEL USE_MIPI_PANEL
#endif

#ifndef DEMO_DISPLAY_CONTROLLER
/* Use LCDIFV2 by default, could use ELCDIF by changing this macro. */
#define DEMO_DISPLAY_CONTROLLER DEMO_DISPLAY_CONTROLLER_LCDIFV2
#endif

#define DEMO_BUFFER_WIDTH DEMO_PANEL_WIDTH
#define DEMO_BUFFER_HEIGHT DEMO_PANEL_HEIGHT

/*
 * The DPHY bit clock must be fast enough to send out the pixels, it should be
 * larger than:
 *
 *         (Pixel clock * bit per output pixel) / number of MIPI data lane
 *
 * Here the desired DPHY bit clock multiplied by ( 9 / 8 = 1.125) to ensure
 * it is fast enough.
 */
#define DEMO_MIPI_DPHY_BIT_CLK_ENLARGE(origin) (((origin) / 8) * 9)

extern const dc_fb_t g_dc;
extern MIPI_DSI_Type g_mipiDsi;
#define DEMO_MIPI_DSI (&g_mipiDsi)
#define DEMO_MIPI_DSI_LANE_NUM 2

namespace Qul {
namespace Platform {
namespace Private {

void prepareDisplayController(void);
PlatformInterface::Screen *availableScreens(size_t *screenCount);

} // namespace Private
} // namespace Platform
} // namespace Qul
