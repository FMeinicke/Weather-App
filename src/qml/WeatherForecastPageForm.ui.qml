//============================================================================
/// \file   WeatherForecastPageForm.ui.qml
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
      model: 1
      delegate: WeatherDataDelegate {
        day: "Today"
        weatherStateName: weatherApi.weatherData.weatherStateName
        weatherStateAbbr: weatherApi.weatherData.weatherStateAbbreviation
        theTemp: weatherApi.weatherData.theTemp
        minTemp: weatherApi.weatherData.minTemp
        maxTemp: weatherApi.weatherData.maxTemp
      }
    }
  }
}
