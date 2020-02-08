//============================================================================
/// \file   SearchPageForm.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06.02.2020
/// \brief  A page providing a search bar to search for locations
//============================================================================
import QtQuick 2.12
import QtQuick.Window 2.3
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
  id: root

  title: qsTr("Weather Forecast")

  width: ScreenInfo.width
  height: ScreenInfo.height

  ColumnLayout {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: 10

    SearchBox {
      id: searchBox

      placeholderText: "Search"

      Layout.preferredHeight: 35

      onTextEdited: console.log(text)
    }

    // results
  }

  Connections {
    target: weatherApi
    onDataReady: {
      console.log(mydata)
    }
  }
}

