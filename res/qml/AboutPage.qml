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
/// \file   AboutPage.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   26/02/2020
/// \brief  A page displaying information about the app
//============================================================================
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
  id: page

  title: qsTr("About")

  ColumnLayout {
    id: layout

    width: parent.width - 2 * spacing
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.topMargin: 2 * spacing
    spacing: 10

    Text {
      id: txtAppName

      text: "Mobile Weather"
      font.pixelSize: Qt.application.font.pixelSize * 2
      font.weight: Font.Bold

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter
    }

    Text {
      id: txtAppVersion

      text: qsTr("Version %1").arg(Qt.application.version)
      font.pixelSize: Qt.application.font.pixelSize * 1.4

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter
    }

    Image {
      id: imgAppIcon

      source: "qrc:/icons/weather_app"
      sourceSize.height: 75

      Layout.fillWidth: true
      fillMode: Image.PreserveAspectFit
    }

    Text {
      id: txtCopyright

      text: qsTr("Copyright (c) 2020 Florian Meinicke")
      font.pixelSize: Qt.application.font.pixelSize

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter
    }

    Text {
      id: txtLicense

      text: qsTr("<html>Licensed under " +
                 "<a href='https://opensource.org/licenses/MIT'>MIT License" +
                 "</a></html>")
      textFormat: Text.RichText
      font.pixelSize: Qt.application.font.pixelSize
      wrapMode: Text.WordWrap

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter

      onLinkActivated: Qt.openUrlExternally(link)
    }

    ToolSeparator {
      orientation: Qt.Horizontal
      Layout.fillWidth: true
      hoverEnabled: false
    }

    Text {
      id: txtCredits

      text: qsTr("Credits and Icon Sources")
      font.pixelSize: Qt.application.font.pixelSize * 1.2
      font.weight: Font.DemiBold

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter
    }

    Text {
      text: qsTr("<html>This app uses the free API available at " +
                 "<a href='https://www.metaweather.com'>MetaWeather.com</a>. " +
                 "All weather icons as well as the app icon are taken from " +
                 "there.</html>")
      textFormat: Text.RichText
      font.pixelSize: Qt.application.font.pixelSize
      wrapMode: Text.WordWrap

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter

      onLinkActivated: Qt.openUrlExternally(link)
    }

    Text {
      text: qsTr("<html>Material Icons: Downloaded from " +
                 "<a href='https://www.material.io/resources/icons/'>" +
                 "material.io</a></html>")
      textFormat: Text.RichText
      font.pixelSize: Qt.application.font.pixelSize
      wrapMode: Text.WordWrap

      Layout.fillWidth: true
      horizontalAlignment: Text.AlignHCenter

      onLinkActivated: Qt.openUrlExternally(link)
    }
  }
}
