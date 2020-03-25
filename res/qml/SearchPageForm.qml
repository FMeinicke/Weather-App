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
/// \file   SearchPageForm.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06/02/2020
/// \brief  A page providing a search bar to search for locations
//============================================================================
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Page {
  id: root

  padding: 5

  title: qsTr("Weather Forecast")

  ColumnLayout {
    width: parent.width

    anchors.horizontalCenter: parent.horizontalCenter
    anchors.top: parent.top
    anchors.topMargin: 10
    spacing: -root.padding

    SearchBox {
      id: searchBox

      placeholderText: "Search"

      Layout.preferredHeight: 35
      Layout.alignment: Qt.AlignHCenter

      onTextEdited: weatherApi.requestLocation(text)

      onCleared: {
        locationResultsModel.clear()
        lblOops.visible = false
      }
    }

    Label {
      id: lblOops

      Layout.topMargin: 4 * root.padding
      Layout.fillWidth: true

      visible: false

      text: qsTr("Oops! Couldn't find the location you're looking for. " +
                 "Try a bigger city near you to get an approximate forecast")
      font.pointSize: Qt.application.font.pointSize * 1.1
      horizontalAlignment: Text.AlignHCenter
      wrapMode: Text.WordWrap
    }

    ListView {
      id: locationResults

      Layout.alignment: Qt.AlignHCenter
      Layout.topMargin: 2 * root.padding
      height: contentHeight
      width: searchBox.width - 2 * root.padding

      Rectangle {
        z: -1
        anchors.fill: parent
        anchors.topMargin: -root.padding
        anchors.leftMargin: root.padding

        border.color: "black"
        radius: 3

        visible: locationResultsModel.count > 0
      }

      model: ListModel {
        id: locationResultsModel
      }

      delegate: Button {
        id: button

        flat: true

        onClicked: {
          weatherApi.setLocationByIndex(index)
          weatherApi.requestWeatherData()
          stackView.pop()
        }

        height: 30
        width: locationResults.width - root.padding

        display: Button.IconOnly
        text: location

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
      lblOops.visible = (locations.length === 0)

      locationResultsModel.clear()
      for (let location of locations) {
        locationResultsModel.append({"location": location})
      }
    }
  }
}
