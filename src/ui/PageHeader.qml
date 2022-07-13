// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15

import org.kde.kirigami 2.20 as Kirigami

import org.kde.licentia 1.0

RowLayout {
    id: pageHeader

    Layout.fillWidth: true
    spacing: 0

    Kirigami.Heading {
        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
        Layout.leftMargin: Kirigami.Units.largeSpacing + Kirigami.Units.smallSpacing

        text: i18n("Original License")
        level: 3
    }

    Item {
        Layout.fillWidth: true
    }

    QQC2.ToolButton {
        focusPolicy: Qt.NoFocus

        display: QQC2.AbstractButton.IconOnly
        action: Kirigami.Action {
            text: i18n("Copy License to Clipboard (Ctrl+C)")
            icon.name: "edit-copy"
            shortcut: StandardKey.Copy
            onTriggered: {
                textarea.selectAll()
                textarea.copy()
                textarea.moveCursorSelection(0, TextEdit.SelectCharacters)
                textarea.deselect()
            }
        }

        QQC2.ToolTip.visible: hovered
        QQC2.ToolTip.text: text
        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
    }
}
