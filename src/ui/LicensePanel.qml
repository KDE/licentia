import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15

import org.kde.kirigami 2.20 as Kirigami

Kirigami.OverlayDrawer {
    id: licensePanel

    property string description
    property string implementation
    property string permissions
    property string conditions
    property string limitations

    interactive: contentHeight > height
    edge: Kirigami.Settings.isMobile ? Qt.BottomEdge : Qt.application.layoutDirection == Qt.RightToLeft ? Qt.LeftEdge : Qt.RightEdge
    modal: false

    width: Kirigami.Units.gridUnit * 18
    height: applicationWindow().height

    topPadding: 0
    bottomPadding: 0
    leftPadding: 0
    rightPadding: 0

    Kirigami.Theme.colorSet: Kirigami.Theme.Window

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

                    text: i18n("Implementation:")
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
                QQC2.Label {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: licensePanel.permissions
                    wrapMode: Text.Wrap
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Conditions:")
                }
                QQC2.Label {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: licensePanel.conditions
                    wrapMode: Text.Wrap
                }

                Kirigami.Heading {
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter

                    type: Kirigami.Heading.Type.Primary
                    level: 4

                    text: i18n("Limitations:")
                }
                QQC2.Label {
                    Layout.fillWidth: true
                    Layout.bottomMargin: Kirigami.Units.gridUnit

                    text: licensePanel.limitations
                    wrapMode: Text.Wrap
                }
            }
        }
        Item {
            Layout.preferredHeight: Kirigami.Units.gridUnit
        }
    }
}
