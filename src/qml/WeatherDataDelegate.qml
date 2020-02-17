//============================================================================
/// \file   WeatherDataDelegate.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   17/02/2020
/// \brief  A delegate displaying the weather data of one day
//============================================================================
import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

ItemDelegate {
  id: root

  width: Screen.width
  height: layout.height * 1.4

  property string day: "Today"
  property string weatherState: "Cloudy"
  property real theTemp: 3
  property real minTemp: 0
  property real maxTemp: 4

  property int offset: 10

  Rectangle {
    id: rectBorder

    z: -1
    border.width: 1
    border.color: "#10000000"

    anchors.fill: parent
    anchors.topMargin: root.offset
    anchors.leftMargin: root.offset
    anchors.rightMargin: root.offset

    GridLayout {
      id: layout

      anchors.top: parent.top
      anchors.topMargin: root.offset
      anchors.left: parent.left
      anchors.leftMargin: root.offset

      Label {
        id: lblDay

        text: qsTr(root.day)
        color: "#90000000"
      }

      Label {
        id: lblTheTemp

        text: qsTr("%1 °C").arg(root.theTemp)
        font.pointSize: Qt.application.font.pointSize * 1.4

        Layout.row: 1
      }

      Label {
        id: lblWeatherState

        text: qsTr(root.weatherState)
        font.pointSize: Qt.application.font.pointSize * 1.4

        Layout.row: 1
        Layout.column: 1
      }

      Label {
        id: lblMinTemp

        text: qsTr("Min: %1 °C").arg(root.minTemp)

        Layout.row: 2
      }

      Label {
        id: lblMaxTemp

        text: qsTr("Max: %1 °C").arg(root.maxTemp)

        Layout.row: 3
      }
    }
  }

  DropShadow {
      anchors.fill: rectBorder
      horizontalOffset: 2
      verticalOffset: 2
      radius: 4.0
      color: "#80000000"
      source: rectBorder
  }
}
