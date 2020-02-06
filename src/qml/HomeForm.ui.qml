//============================================================================
/// \file   HomeForm.ui.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06.02.2020
/// \brief
//============================================================================
import QtQuick 2.12
import QtQuick.Controls 2.5

Page {
  title: qsTr("Weather Forecast")

  Label {
    text: qsTr("You are on the home page.")
    anchors.centerIn: parent
  }
}
