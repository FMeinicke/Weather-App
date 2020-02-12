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

  padding: 5

  title: qsTr("Weather Forecast")

  width: ScreenInfo.width
  height: ScreenInfo.height

  ColumnLayout {
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: 10
    spacing: -root.padding

    SearchBox {
      id: searchBox

      placeholderText: "Search"

      Layout.preferredHeight: 35

      onTextEdited: weatherApi.requestLocation(text)
    }

    ListView {
      id: locationResults

      Layout.topMargin: 10
      height: contentHeight
      width: searchBox.width - 2 * root.padding

      Rectangle {
        z: -1
        anchors.fill: parent
        anchors.topMargin: -root.padding
        anchors.leftMargin: 2 * root.padding

        border.color: "black"
        radius: 3

        visible: locationResultsModel.count > 0
      }

      model: ListModel {
        id: locationResultsModel
// dummy elements:
//        ListElement { name: "San Francisco" }
//        ListElement { name: "San Diego" }
//        ListElement { name: "San Jose" }
//        ListElement { name: "San Antonio" }
//        ListElement { name: "Santa Cruz" }
//        ListElement { name: "Santiago" }
//        ListElement { name: "Santorini" }
//        ListElement { name: "Santander" }
//        ListElement { name: "Busan" }
//        ListElement { name: "Santa Cruz de Tenerife" }
//        ListElement { name: "Santa Fe" }
      }

      delegate: Button {
        id: button

        flat: true

        height: 30
        width: locationResults.width - root.padding

        display: Button.IconOnly
        text: name
        contentItem: Row {
          spacing: root.padding

          Image {
            source: "qrc:/icons/search_black"
            height: 12
            fillMode: Image.PreserveAspectFit
            anchors.verticalCenter: parent.verticalCenter
          }
          Text {
            text: button.text
            verticalAlignment: Text.AlignVCenter
            anchors.verticalCenter: parent.verticalCenter
          }
        }
        topInset: -root.padding / 2
        topPadding: 0
        bottomInset: root.padding / 2
        bottomPadding: 0
        leftInset: 3 * root.padding
        leftPadding: 5 * root.padding
      }
    }
  }

  Connections {
    target: weatherApi
    onLocationsReady: {
      for (let location of locations) {
        console.log(location)
        locationResultsModel.append({"name": location})
      }
    }
  }
}

