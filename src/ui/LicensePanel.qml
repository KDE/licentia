// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15

import org.kde.kirigami 2.20 as Kirigami

Kirigami.OverlayDrawer {
    id: licensePanel

    property string description
    property string implementation
    property string spdx
    property var permissions
    property var conditions
    property var limitations
    property var using

    interactive: contentHeight > height
    edge: Kirigami.Settings.isMobile ? Qt.BottomEdge : Qt.application.layoutDirection == Qt.RightToLeft ? Qt.LeftEdge : Qt.RightEdge
    modal: false

    width: Kirigami.Units.gridUnit * 20
    height: applicationWindow().height

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    Kirigami.Theme.colorSet: Kirigami.Theme.Window

    component ToolTip : QQC2.ToolTip {
        id: tooltip

        contentItem: RowLayout {
            QQC2.Label {
                Layout.fillWidth: true
                Layout.maximumWidth: Screen.pixelDensity * 63.5 * Screen.devicePixelRatio

                Kirigami.Theme.colorSet: Kirigami.Theme.Tooltip

                text: tooltip.text
                wrapMode: Text.WordWrap
                color: Kirigami.Theme.textColor
            }
        }
    }

    contentItem: ColumnLayout {
        clip: true
        spacing: 0

        QQC2.ToolBar {
            Layout.fillWidth: true
            implicitHeight: applicationWindow().pageStack.globalToolBar.preferredHeight

            RowLayout {
                anchors.fill: parent
                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    Layout.leftMargin: Kirigami.Units.largeSpacing + Kirigami.Units.smallSpacing

                    level: 3

                    text: i18n("About This License")
                }

                Item {
                    Layout.fillWidth: true
                }

                QQC2.ToolButton {
                    display: QQC2.AbstractButton.IconOnly
                    action: Kirigami.Action {
                        text: i18n("License Source")
                        icon.name: "edit-link"
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
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: licensePanel.implementation
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

                            ToolTip {
                                parent: parent
                                visible: parent.hovered
                                text: modelData.description
                                delay: Kirigami.Units.toolTipDelay
                            }
                        }
                    }
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Conditions:")
                }
                Flow {
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

                            ToolTip {
                                parent: parent
                                visible: parent.hovered
                                text: modelData.description
                                delay: Kirigami.Units.toolTipDelay
                            }
                        }
                    }
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Limitations:")
                }
                Flow {
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

                            ToolTip {
                                parent: parent
                                visible: parent.hovered
                                text: modelData.description
                                delay: Kirigami.Units.toolTipDelay
                            }
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
                Flow {
                    visible: licensePanel.using.length > 0

                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    spacing: Kirigami.Units.largeSpacing

                    Repeater {
                        model: licensePanel.using

                        Kirigami.UrlButton {
                            Layout.fillWidth: true

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
