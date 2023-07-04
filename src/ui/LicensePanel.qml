// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

import org.kde.kirigami 2.20 as Kirigami

Kirigami.ContextDrawer {
    id: licensePanel

    property string description
    property string fileImplementation
    property string spdxImplementation
    property string spdx
    property var permissions
    property var conditions
    property var limitations
    property var using

    readonly property bool smallScreen: applicationWindow().width < Kirigami.Units.gridUnit * 40

    interactive: modal || contentHeight > height
    edge: Qt.application.layoutDirection == Qt.RightToLeft ? Qt.LeftEdge : Qt.RightEdge
    modal: smallScreen
    onModalChanged: drawerOpen = !modal;
    drawerOpen: !modal

    width: Math.min(applicationWindow().width, Kirigami.Units.gridUnit * 20)

    handleVisible: true
    handleClosedIcon.source: modal ? null : "sidebar-expand-left"
    handleOpenIcon.source: modal ? null : "sidebar-collapse-left"

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    enabled: true

    Kirigami.Theme.colorSet: Kirigami.Theme.Window
    Kirigami.Theme.inherit: false

    contentItem: ColumnLayout {
        clip: true
        spacing: 0

        QQC2.ToolBar {
            Layout.fillWidth: true
            Layout.preferredHeight: applicationWindow().pageStack.globalToolBar.preferredHeight

            leftPadding: 3
            rightPadding: 3
            topPadding: 3
            bottomPadding: 3

            contentItem: RowLayout {
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.leftMargin: Kirigami.Units.largeSpacing + Kirigami.Units.smallSpacing
                    Layout.fillWidth: true

                    level: 3

                    text: i18nc("About [License SPDX identifier]", "About %1", licensePanel.spdx)
                }

                QQC2.ToolButton {
                    display: QQC2.AbstractButton.IconOnly
                    action: Kirigami.Action {
                        text: i18n("License Source")
                        icon.name: "link"
                        onTriggered: Qt.openUrlExternally(`https://spdx.org/licenses/${licensePanel.spdx}`)
                    }

                    QQC2.ToolTip.visible: hovered
                    QQC2.ToolTip.text: text
                    QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                }
            }
        }

        QQC2.ScrollView {
            id: scroll

            clip: true
            contentWidth: availableWidth

            Layout.fillWidth: true
            Layout.fillHeight: true

            QQC2.ScrollBar.horizontal.policy: QQC2.ScrollBar.AlwaysOff

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: Kirigami.Units.gridUnit

                QQC2.Label {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: licensePanel.description
                    wrapMode: Text.Wrap
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("How to:")
                }
                QQC2.Label {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.largeSpacing

                    text: licensePanel.fileImplementation
                    wrapMode: Text.Wrap
                }
                QQC2.Label {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: licensePanel.spdxImplementation
                    wrapMode: Text.Wrap
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Permissions:")
                }
                Flow {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    spacing: Kirigami.Units.largeSpacing

                    Repeater {
                        model: licensePanel.permissions
                        delegate: Kirigami.Chip {
                            checked: false
                            checkable: false

                            text: modelData.name

                            closable: false

                            QQC2.ToolTip.visible: hovered
                            QQC2.ToolTip.text: modelData.description
                            QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                        }
                    }
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Conditions:")
                }
                QQC2.Label {
                    visible: licensePanel.conditions.length <= 0

                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: i18n("(no conditions)")
                }
                Flow {
                    visible: licensePanel.conditions.length > 0

                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    spacing: Kirigami.Units.largeSpacing

                    Repeater {
                        model: licensePanel.conditions
                        delegate: Kirigami.Chip {
                            checked: false
                            checkable: false

                            text: modelData.name

                            closable: false

                            QQC2.ToolTip.visible: hovered
                            QQC2.ToolTip.text: modelData.description
                            QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                        }
                    }
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Limitations:")
                }
                QQC2.Label {
                    visible: licensePanel.limitations.length <= 0

                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: i18n("(no limitations)")
                }
                Flow {
                    visible: licensePanel.limitations.length > 0

                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    spacing: Kirigami.Units.largeSpacing

                    Repeater {
                        model: licensePanel.limitations
                        delegate: Kirigami.Chip {
                            checked: false
                            checkable: false

                            text: modelData.name

                            closable: false

                            QQC2.ToolTip.visible: hovered
                            QQC2.ToolTip.text: modelData.description
                            QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                        }
                    }
                }

                Kirigami.Heading {
                    visible: licensePanel.using.length > 0

                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Projects using:")
                }
                ColumnLayout {
                    visible: licensePanel.using.length > 0

                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    spacing: Kirigami.Units.largeSpacing

                    Repeater {
                        model: licensePanel.using

                        Kirigami.UrlButton {
                            text: modelData.name
                            url: modelData.url
                        }
                    }
                }

                Item {
                    Layout.preferredHeight: Kirigami.Units.gridUnit
                }
            }
        }
    }
}
