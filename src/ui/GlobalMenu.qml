// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import Qt.labs.platform as Labs

import org.kde.kirigami as Kirigami

import org.kde.licentia

Labs.MenuBar {
    id: menuBar

    Labs.Menu {
        title: i18nc("@menu", "File")

        Labs.MenuItem {
            text: i18nc("@menu-action", "Quit")
            icon.name: "application-exit"
            shortcut: StandardKey.Quit
            onTriggered: Qt.quit()
        }
    }

    Labs.Menu {
        title: i18nc("@menu", "Edit")

        Labs.MenuItem {
            text: i18nc("@menu-action", "Copy license to clipboard")
            icon.name: "edit-copy"
            shortcut: StandardKey.Copy
            onTriggered: {
                textarea.selectAll()
                textarea.copy()
                textarea.moveCursorSelection(0, TextEdit.SelectCharacters)
                textarea.deselect()
            }
        }
    }

    Labs.Menu {
        title: i18nc("@menu", "Help")

        Labs.MenuItem {
            text: i18nc("@menu-action", "Report Bug…")
            icon.name: "tools-report-bug"
            onTriggered: Qt.openUrlExternally(AboutType.aboutData.bugAddress);
        }

        Labs.MenuItem {
            text: i18nc("@menu-action", "About Licentia")
            icon.name: "help-about"
            shortcut: StandardKey.HelpContents
            onTriggered: pageStack.pushDialogLayer(Qt.resolvedUrl("About.qml"), {}, {
                title: i18n("About Licentia"),
                width: Kirigami.Units.gridUnit * 25,
                height: Kirigami.Units.gridUnit * 30
            })
            enabled: pageStack.layers.depth <= 1
        }
    }
}
