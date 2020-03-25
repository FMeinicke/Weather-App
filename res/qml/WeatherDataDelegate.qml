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
  height: layoutMain.height + 2 * offset

  property string date: "Today"
  property string weatherStateName: "Cloudy"
  property string weatherStateAbbr: "c"
  property real theTemp: 3
  property real minTemp: 0
  property real maxTemp: 4
  property real windSpeed: 11
  property real windDirection: 247.5
  property string windDirCompass: "WSW"
  property real pressure: 1010
  property real humidity: 79
  property real visibility: 10
  property real confidence: 77
  property date sunrise: "2020-02-23 07:32"
  property date sunset: "2020-02-23 18:14"

  property int offset: 10

  state: "minimal"

  states: [
    State {
      name: "minimal"
      PropertyChanges {
        target: layoutMore
        visible: false
      }
      PropertyChanges {
        target: btnShowMore
        text: qsTr("Full forecast")
      }
    },
    State {
      name: "expanded"
      PropertyChanges {
        target: layoutMore
        visible: true
      }
      PropertyChanges {
        target: btnShowMore
        text: qsTr("Show less")
      }
    }
  ]

  Rectangle {
    id: rectBorder

    z: -1
    border.width: 1
    border.color: "#10000000"

    anchors.fill: parent
    anchors.topMargin: root.offset
    anchors.leftMargin: root.offset
    anchors.rightMargin: root.offset

    ColumnLayout {
      id: layoutMain

      anchors.top: parent.top
      anchors.topMargin: root.offset
      anchors.left: parent.left
      anchors.leftMargin: root.offset

      GridLayout {
        id: layoutLess

        Label {
          id: lblDate

          text: qsTr(root.date)
          color: "#90000000"

          Layout.columnSpan: 2
        }

        Label {
          id: lblTheTemp

          text: qsTr("%1 °C").arg(root.theTemp.toPrecision(2))
          font.pointSize: Qt.application.font.pointSize * 1.4

          Layout.row: 1
        }

        Label {
          id: lblWeatherState

          text: qsTr(root.weatherStateName)
          font.pointSize: Qt.application.font.pointSize * 1.4
        }

        Image {
          id: imgWeatherState

          source: "https://www.metaweather.com/static/img/weather/png/"
                  + root.weatherStateAbbr + ".png"
          sourceSize.height: 48

          fillMode: Image.PreserveAspectFit

          Layout.leftMargin: root.offset
          autoTransform: true
        }

        Label {
          id: lblMinTemp

          text: qsTr("Min: %1 °C").arg(root.minTemp.toPrecision(2))

          Layout.row: 2
        }

        Label {
          id: lblMaxTemp

          text: qsTr("Max: %1 °C").arg(root.maxTemp.toPrecision(2))

          Layout.row: 3
        }
      }

      GridLayout {
        id: layoutMore

        Layout.row: 1

        Label {
          id: lblWind

          text: qsTr("Wind: %1 km/h").arg(root.windSpeed.toPrecision(3))

          Layout.row: 4
          Layout.topMargin: root.offset * 1.5
        }

        Image {
          id: imgWindDir

          source: "qrc:/icons/windarrow"
          sourceSize.height: 16
          fillMode: Image.PreserveAspectFit
          rotation: root.windDirection

          Layout.topMargin: root.offset
        }

        Label {
          id: lblPressure

          text: qsTr("Air Pressure: %1 hPa").arg(root.pressure)

          Layout.topMargin: root.offset * 1.5
          Layout.leftMargin: root.offset * 3
        }

        Label {
          id: lblHumidity

          text: qsTr("Humidity: %1%").arg(root.humidity)

          Layout.row: 5
          Layout.columnSpan: 3
          Layout.topMargin: root.offset * 1.5
        }

        Label {
          id: lblVisibility

          text: qsTr("Visibility: %1 km").arg(root.visibility.toPrecision(2))

          Layout.row: 6
          Layout.columnSpan: 3
          Layout.topMargin: root.offset * 1.5
        }

        Label {
          id: lblSunrise

          text: qsTr("Sunrise: %1").arg(Qt.formatDateTime(root.sunrise, "hh:mm"))

          Layout.row: 7
          Layout.columnSpan: 3
          Layout.topMargin: root.offset * 1.5
        }

        Label {
          id: lblSunset

          text: qsTr("Sunset: %1").arg(Qt.formatDateTime(root.sunset, "hh:mm"))

          Layout.row: 8
          Layout.columnSpan: 3
        }
      }

      Button {
        id: btnShowMore

        text: qsTr("Full forecast")
        flat: true

        Layout.row: 2

        onClicked: root.state === "minimal" ? root.state = "expanded" :
                                              root.state = "minimal"
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
