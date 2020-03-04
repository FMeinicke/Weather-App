//============================================================================
/// \file   WeatherForecastPageForm.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   18/02/2020
/// \brief  A page displaying the weather forecast for the selected location
//============================================================================
import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.12

Page {
  id: root

  property bool apiRequestRunning: true

  objectName: "WeatherForcastPage"

  title: weatherApi.locationName

  Connections {
    target: weatherApi
    onWeatherDataModelChanged: root.apiRequestRunning = false
  }

  BusyIndicator {
        id: busyIndicator

        running: root.apiRequestRunning

        height: 40
        width: height
        z: 1

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 10

        background: Rectangle {
          id: rectBackground

          visible: root.apiRequestRunning
          color: "white"
          radius: 100
        }

        DropShadow {
          anchors.fill: rectBackground
          radius: 5.0
          color: "#60000000"
          source: rectBackground
          visible: rectBackground.visible
        }
      }

  ListView {
    id: weatherDataView

    property bool flicked: false

    anchors.fill: parent
    width: parent.width

    model: root.apiRequestRunning ? 0 : weatherApi.weatherDataModel
    delegate: WeatherDataDelegate {
      date: {
        if (index === 0) {
          return qsTr("Today")
        } else if (index === 1) {
          return qsTr("Tomorrow")
        } else {
          return Qt.formatDate(model.date, "dddd, dd/MM/yyyy")
        }
      }
      weatherStateName: model.weatherStateName
      weatherStateAbbr: model.weatherStateAbbr
      theTemp: model.theTemp
      minTemp: model.minTemp
      maxTemp: model.maxTemp
      windSpeed: model.windSpeed
      windDirection: model.windDirection
      windDirCompass: model.windDirCompass
      pressure: model.airPressure
      humidity: model.humidity
      visibility: model.visibility
      confidence: model.confidence
      sunrise: model.sunriseTime
      sunset: model.sunsetTime
    }
  }
}
