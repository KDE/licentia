// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15

import org.kde.kirigami 2.20 as Kirigami
import org.kde.kitemmodels 1.0

import org.kde.licentia 1.0

Kirigami.ApplicationWindow {
    id: root

    title: i18n("Licentia")

    minimumWidth: Kirigami.Units.gridUnit * 10
    minimumHeight: Kirigami.Units.gridUnit * 10

    Timer {
        id: saveWindowGeometryTimer
        interval: 1000
        onTriggered: App.saveWindowGeometry(root)
    }

    Connections {
        id: saveWindowGeometryConnections
        enabled: root.visible
        target: root

        function onClosing() { App.saveWindowGeometry(root); }
        function onWidthChanged() { saveWindowGeometryTimer.restart(); }
        function onHeightChanged() { saveWindowGeometryTimer.restart(); }
        function onXChanged() { saveWindowGeometryTimer.restart(); }
        function onYChanged() { saveWindowGeometryTimer.restart(); }
    }

    Loader {
        active: !Kirigami.Settings.isMobile
        sourceComponent: GlobalMenu {}
    }

    globalDrawer: Kirigami.OverlayDrawer {
        edge: Qt.application.layoutDirection === Qt.RightToLeft ? Qt.RightEdge : Qt.LeftEdge
        modal: Kirigami.Settings.isMobile || (applicationWindow().width < Kirigami.Units.gridUnit * 50 && !collapsed) // Only modal when not collapsed, otherwise collapsed won't show.
        onModalChanged: drawerOpen = !modal;
        drawerOpen: !Kirigami.Settings.isMobile
        handleVisible: modal
        handleClosedIcon.source: modal ? null : "sidebar-expand-left"
        handleOpenIcon.source: modal ? null : "sidebar-collapse-left"
        width: Kirigami.Units.gridUnit * 16

        Kirigami.Theme.colorSet: Kirigami.Theme.Window

        leftPadding: 0
        rightPadding: 0
        topPadding: 0
        bottomPadding: 0

        contentItem: ColumnLayout {
            id: container
            spacing: 0
            clip: true

            QQC2.ToolBar {
                id: toolbar
                Layout.fillWidth: true
                Layout.preferredHeight: pageStack.globalToolBar.preferredHeight

                leftPadding: Kirigami.Units.smallSpacing
                rightPadding: Kirigami.Units.smallSpacing
                topPadding: 0
                bottomPadding: 0

                RowLayout {
                    anchors.fill: parent
                    spacing: Kirigami.Units.smallSpacing / 2

                    Kirigami.SearchField {
                        id: searchField
                        Layout.fillWidth: true

                        KeyNavigation.tab: aboutButton
                    }

                    QQC2.ToolButton {
                        id: aboutButton

                        focusPolicy: Qt.NoFocus
                        KeyNavigation.tab: listview

                        display: QQC2.AbstractButton.IconOnly
                        action: Kirigami.Action {
                            text: i18nc("@menu-action", "About Licentia")
                            icon.name: "help-about"
                            shortcut: StandardKey.HelpContents
                            onTriggered: pageStack.pushDialogLayer(Qt.resolvedUrl("About.qml"), {}, {
                                title: i18n("About Licentia"),
                                width: Kirigami.Units.gridUnit * 20,
                                height: Kirigami.Units.gridUnit * 30
                            })
                            enabled: pageStack.layers.depth <= 1
                        }

                        QQC2.ToolTip.visible: hovered
                        QQC2.ToolTip.text: text
                        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                    }
                }
            }

            QQC2.ScrollView {
                clip: true
                implicitWidth: Kirigami.Units.gridUnit * 16
                contentWidth: availableWidth

                Layout.fillWidth: true
                Layout.fillHeight: true

                QQC2.ScrollBar.horizontal.policy: QQC2.ScrollBar.AlwaysOff

                ListView {
                    id: listview

                    KeyNavigation.tab: page
                    activeFocusOnTab: true

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    currentIndex: 0
                    model: KSortFilterProxyModel {
                        id: filteredModel
                        sourceModel: LicensesModel { id: licensesModel }
                        filterRole: "name"
                        sortRole: "name"
                        filterRegularExpression: {
                            if (searchField.text === "") return new RegExp()
                            return new RegExp("%1".arg(searchField.text), "i")
                        }
                    }
                    delegate: Kirigami.BasicListItem {
                        id: basiclistitem

                        separatorVisible: false

                        label: model.name

                        onClicked: {
                            root.title = model.name

                            textarea.text = model.body

                            licensePanel.description = model.description
                            licensePanel.fileImplementation = model.fileImplementation
                            licensePanel.spdxImplementation = model.spdxImplementation

                            licensePanel.permissions = model.permissions
                            licensePanel.conditions = model.conditions
                            licensePanel.limitations = model.limitations
                            licensePanel.using = model.using
                            licensePanel.spdx = model.spdx
                        }

                        QQC2.ToolTip.visible: hovered && labelItem.truncated
                        QQC2.ToolTip.text: label
                        QQC2.ToolTip.delay: Kirigami.Units.toolTipDelay
                    }
                }
            }
        }
    }

    contextDrawer: LicensePanel {
        id: licensePanel
    }

    pageStack.initialPage: Kirigami.Page {
        id: page

        padding: 0
        titleDelegate: PageHeader {}

        QQC2.ScrollView {
            anchors.fill: parent

            QQC2.TextArea {
                id: textarea

                padding: 0
                textMargin: Kirigami.Units.largeSpacing * 2

                readOnly: true
                wrapMode: Text.Wrap

                background: Rectangle {
                    Kirigami.Theme.colorSet: Kirigami.Theme.View
                    Kirigami.Theme.inherit: false
                    color: Kirigami.Theme.backgroundColor
                }
            }
        }
    }

    Component.onCompleted: {
        listview.currentItem.clicked()
    }
}
