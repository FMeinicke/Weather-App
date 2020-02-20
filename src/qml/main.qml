//============================================================================
/// \file   main.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06/02/2020
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
        Layout.alignment: Qt.AlignCenter
      }

      ToolButton {
        id: searchButton

        property Item currentSearchPage

        icon.source: "qrc:/icons/search_white"
        icon.color: 'transparent'
        Layout.alignment: Qt.AlignRight
        onClicked: {
          // prevent "SearchPageForm" to be pushed onto the stack multiple times
          if (!currentSearchPage || currentSearchPage != stackView.currentItem) {
            currentSearchPage = stackView.push("SearchPageForm.qml")
          }
        }
      }

      ToolButton {
        id: menuButton

        text: "\u22ee"

        Layout.maximumWidth: height / 2
        Layout.alignment: Qt.AlignTop
        font.pixelSize: Qt.application.font.pixelSize * 1.6

        onClicked: menu.toggle()
      }
    }
  }

  Menu {
    id: menu

    property bool isOpen: false

    x: window.width - width - 2
    width: favMenu.implicitWidth

    MenuItem {
      id: favMenu
      text: qsTr("Add Location to Favourites")
      enabled: stackView.currentItem.objectName === "WeatherForcastPage"

      onTriggered: weatherApi.addCurrentLocationToFavourites()
    }

    function toggle() {
      if (isOpen) {
        close()
      } else {
        open()
      }
      isOpen = !isOpen
    }
  }

  Drawer {
    id: drawer

    width: window.width * 0.66
    height: window.height

//    Column {
//      anchors.fill: parent

//      ItemDelegate {
//        text: qsTr("Page 1")
//        width: parent.width
//        onClicked: {
//          stackView.push("Page1Form.ui.qml")
//          drawer.close()
//        }
//      }
//      ItemDelegate {
//        text: qsTr("Page 2")
//        width: parent.width
//        onClicked: {
//          stackView.push("Page2Form.ui.qml")
//          drawer.close()
//        }
//      }
//    }
  }

  StackView {
    id: stackView
    initialItem: "WeatherForecastPageForm.ui.qml"
    anchors.fill: parent
  }

  /**
   * @brief Replaces the WeatherForecastPageForm with the HomeForm in case the
   * app has been started for the first time to show the landing page.
   */
  function setFirstStartPage() {
    stackView.replace("HomeForm.ui.qml");
  }
}
