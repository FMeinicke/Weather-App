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
  id: page
  width: ScreenInfo.width
  height: ScreenInfo.height

  Label {
    id: label

    text: qsTr("You are on Search Page.")
    anchors.centerIn: parent
  }

  Button {
    id: button

    text: qsTr("check")
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: label.bottom
    anchors.topMargin: -10
    onClicked: {
      weatherApi.requestData()
    }
  }

  Connections {
    target: weatherApi
    onDataReady: {
      console.log(data)
      label.text = qsTr(data)
    }
  }
}

