//============================================================================
/// \file   main.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06.02.2020
/// \brief  The starting screen of the app
//============================================================================
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.3
import QtQuick.Layouts 1.12

ApplicationWindow {
  id: window

  visible: true
  width: ScreenInfo.width
  height: ScreenInfo.height

  header: ToolBar {
    contentHeight: hamburgerMenuButton.implicitHeight
    contentWidth: ScreenInfo.width

    RowLayout {
      anchors.fill: parent
      Component.onCompleted: {
        console.log("width: " + width + ", height: " + height)
      }

      ToolButton {
        id: hamburgerMenuButton

        text: stackView.depth > 1 ? "\u25c4" : "\u2261"
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        onClicked: {
          if (stackView.depth > 1) {
            stackView.pop()
          } else {
            drawer.open()
          }
        }
      }

      Label {
        text: stackView.currentItem.title
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        anchors.centerIn: parent
      }

      ToolButton {
        id: searchButton

        icon.source: "qrc:/icons/search"
        icon.color: 'transparent'
        onClicked: stackView.push("SearchPageForm.qml")
      }
    }
  }

  Drawer {
    id: drawer

    width: window.width * 0.66
    height: window.height

    Column {
      anchors.fill: parent

      ItemDelegate {
        text: qsTr("Page 1")
        width: parent.width
        onClicked: {
          stackView.push("Page1Form.ui.qml")
          drawer.close()
        }
      }
      ItemDelegate {
        text: qsTr("Page 2")
        width: parent.width
        onClicked: {
          stackView.push("Page2Form.ui.qml")
          drawer.close()
        }
      }
    }
  }

  StackView {
    id: stackView
    initialItem: "HomeForm.ui.qml"
    anchors.fill: parent
  }
}
//-----------------------------------------------------------------------------
// for SwipeView//ApplicationWindow {
//  visible: true
//  width: 640
//  height: 480
//  title: qsTr("Scroll")
//  ScrollView {
//    anchors.fill: parent

//    ListView {
//      width: parent.width
//      model: 20
//      delegate: ItemDelegate {
//        text: "Item " + (index + 1)
//        width: parent.width
//      }
//    }
//  }
//}

