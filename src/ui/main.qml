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

    width: Kirigami.Units.gridUnit * 71
    height: Kirigami.Units.gridUnit * 43
    minimumWidth: Kirigami.Units.gridUnit * 50
    minimumHeight: Kirigami.Units.gridUnit * 20

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
        modal: Kirigami.Settings.isMobile
        handleVisible: modal
        handleClosedIcon.source: null
        handleOpenIcon.source: null
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

                    Kirigami.SearchField {
                        id: searchField
                        Layout.fillWidth: true
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

                ColumnLayout {
                    anchors.fill: parent
                    spacing: 0

                    ListView {
                        id: listview

                        interactive: contentHeight > height

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        currentIndex: 0
                        model: KSortFilterProxyModel {
                            id: filteredModel
                            sourceModel: LicensesModel { id: licensesModel }
                            filterRole: "name"
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

                                page.spdx = model.spdx
                                textarea.text = model.body

                                licensePanel.description = model.description
                                licensePanel.implementation = model.implementation
                                licensePanel.permissions = model.permissions.toString().replace(/,/g, ', ')
                                licensePanel.conditions = model.conditions.toString().replace(/,/g, ', ')
                                licensePanel.limitations = model.limitations.toString().replace(/,/g, ', ')
                            }
                        }
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

        property string spdx

        padding: 0
        titleDelegate: PageHeader {
            spdx: page.spdx
        }

        QQC2.ScrollView {
            anchors.fill: parent

            QQC2.TextArea {
                id: textarea

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
