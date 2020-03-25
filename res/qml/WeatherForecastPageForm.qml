/**
 ** This file is part of the "Mobile Weather" project.
 ** Copyright (c) 2020 Florian Meinicke <florian.meinicke@t-online.de>.
 **
 ** Permission is hereby granted, free of charge, to any person obtaining a copy
 ** of this software and associated documentation files (the "Software"), to deal
 ** in the Software without restriction, including without limitation the rights
 ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 ** copies of the Software, and to permit persons to whom the Software is
 ** furnished to do so, subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in all
 ** copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 ** SOFTWARE.
 **/

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

  objectName: "WeatherForecastPage"

  title: weatherApi.locationName

  state: weatherApi.locationName ? "" : "noLocation"

  Connections {
    target: weatherApi

    onWeatherDataRequestStarted: {
      root.apiRequestRunning = true
    }

    onWeatherDataModelChanged: {
      root.apiRequestRunning = false
      // always start with the minimal view for each card
      for (let i = 0; i < weatherDataView.count; ++i) {
        weatherDataView.itemAtIndex(i).state = "minimal"
      }
    }
  }

  BusyIndicator {
    id: busyIndicator

    running: root.apiRequestRunning

    height: 38
    width: height
    z: 1

    padding: 9

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
      radius: 4.0
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

  GridLayout {
    id: helpMessage

    visible: false
    width: parent.width
    anchors.horizontalCenter: parent.horizontalCenter

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

  states: [
    State {
      name: "noLocation"
      PropertyChanges {
        target: root
        title: qsTr("Weather Forecast")
        apiRequestRunning: false
      }
      PropertyChanges {
        target: helpMessage
        visible: true
      }
      PropertyChanges {
        target: weatherDataView
        visible: false
      }
    }
  ]
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
