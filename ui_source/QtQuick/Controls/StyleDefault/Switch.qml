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

import QtQuick 2.15
import QtQuick.Templates 2.15
import QtQuickUltralite.Extras 2.0

Switch {
    id: control

    implicitWidth: Math.max((background ? background.implicitWidth : 0) + leftInset + rightInset,
                            (contentItem ? contentItem.implicitWidth : 0) + leftPadding + rightPadding)
    // TODO: https://bugreports.qt.io/browse/UL-783
//    implicitHeight: Math.max((background ? background.implicitHeight : 0) + topInset + bottomInset,
//                             (contentItem ? contentItem.implicitHeight : 0) + topPadding + bottomPadding,
//                             (indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding)
    implicitHeight: Math.max((background ? background.implicitHeight : 0) + topInset + bottomInset,
                             Math.max((contentItem ? contentItem.implicitHeight : 0) + topPadding + bottomPadding,
                             (indicator ? indicator.implicitHeight : 0) + topPadding + bottomPadding))

    leftPadding: DefaultStyle.padding
    rightPadding: DefaultStyle.padding
    topPadding: DefaultStyle.padding
    bottomPadding: DefaultStyle.padding

    leftInset: DefaultStyle.inset
    topInset: DefaultStyle.inset
    rightInset: DefaultStyle.inset
    bottomInset: DefaultStyle.inset

    spacing: 10

    indicator: ColorizedImage {
        x: control.leftPadding
        y: control.topPadding + (control.availableHeight - height) / 2
        color: checked ? "#5ae0aa" : "#c4c9cc"
        source: "qrc:/images/switch-bg.png"

        // TODO: move both of these into switch-bg.png
        Image {
            x: parent.width * 0.25 - width / 2
            source: "qrc:/images/switch-i.png"
            anchors.verticalCenter: parent.verticalCenter
        }
        Image {
            x: parent.width * 0.75 - width / 2
            source: "qrc:/images/switch-o.png"
            anchors.verticalCenter: parent.verticalCenter
        }

        Image {
            source: "qrc:/images/switch-handle.png"
            // 8 is the space on each side of the handle in the image.
            x: Math.max(-8, Math.min((parent.width - width) + 8,
                control.visualPosition * parent.width - (width / 2)))
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 5

            Behavior on x { NumberAnimation { duration: 150 } }
        }
    }

    // Need a background for insets to work.
    background: Item {
        implicitWidth: 100
        implicitHeight: 42
    }

    // Text has no padding properties in UL, so we use Row with an Item for the spacing.
    contentItem: Row {
        Item {
            implicitWidth: control.indicator ? control.indicator.width + control.spacing : 0
        }

        Text {
            text: control.text
            font: control.font
            color: control.enabled ? DefaultStyle.textColor : DefaultStyle.disabledTextColor
            anchors.verticalCenter: parent.verticalCenter
        }
    }
}
