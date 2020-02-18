//============================================================================
/// \file   HomeForm.ui.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06/02/2020
/// \brief  The home and landing page of the app
//============================================================================
import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
  id: root

  title: state === "" ? weatherApi.locationName : qsTr("Weather Forecast")

  width: ScreenInfo.width
  height: ScreenInfo.height

  state: weatherApi.locationName.length ? "" : "first-time"
  states: [
    State {
      name: "first-time"
      PropertyChanges {
        target: firstTimeDescriptionLayout
        visible: true
      }
      PropertyChanges {
        target: weatherDataView
        visible: false
      }
    }
  ]

  GridLayout {
    id: firstTimeDescriptionLayout

    visible: false

    anchors.horizontalCenter: parent.horizontalCenter
    Image {
      Layout.row: 0
      Layout.column: 1
      Layout.alignment: Qt.AlignRight

      source: "qrc:/icons/double_arrow_black"
      sourceSize.height: 50
      sourceSize.width: height
      fillMode: Image.PreserveAspectFit
      rotation: -60
    }

    Label {
      Layout.row: 1
      Layout.columnSpan: 2
      Layout.fillWidth: true

      text: qsTr("Tap the search icon above to search a location.")
      font.pointSize: Qt.application.font.pointSize * 1.1
      horizontalAlignment: Text.AlignHCenter
    }
  }

  ScrollView {
    id: weatherDataView

    anchors.fill: parent

    ListView {
      width: parent.width
      model: 5
      delegate: WeatherDataDelegate {
        day: weatherApi.weatherData.weatherStateName + (index + 1)
        //        weatherState:
        //        theTemp:
        //        minTemp:
        //        maxTemp:
      }
    }
  }
}
