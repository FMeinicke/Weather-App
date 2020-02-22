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

Page {
  id: root
  objectName: "WeatherForcastPage"

  title: weatherApi.locationName

  width: ScreenInfo.width
  height: ScreenInfo.height

  ScrollView {
    id: weatherDataView

    anchors.fill: parent

    ListView {
      width: parent.width
      model: weatherApi.weatherDataModel
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
      }
    }
  }
}
