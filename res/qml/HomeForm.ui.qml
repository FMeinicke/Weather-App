//============================================================================
/// \file   HomeForm.ui.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06/02/2020
/// \brief  The home and landing page of the app
//============================================================================
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    id: root

    title: qsTr("Weather Forecast")

    GridLayout {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        Image {
            Layout.row: 0
            Layout.alignment: Qt.AlignRight
            Layout.rightMargin: 55

            source: "qrc:/icons/double_arrow_black"
            sourceSize.height: 50
            sourceSize.width: height
            fillMode: Image.PreserveAspectFit
            rotation: -60
        }

        Label {
            Layout.row: 1
            Layout.fillWidth: true

            text: qsTr("Tap the search icon above to search a location.")
            font.pointSize: Qt.application.font.pointSize * 1.1
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
        }
    }
}
