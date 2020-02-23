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
import QtQuick.Controls.Material 2.12
import QtQml.StateMachine 1.0 as DSM

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
        horizontalAlignment: Qt.AlignHCenter
        Layout.fillWidth: true
      }

      ToolButton {
        id: searchButton

        property Item currentSearchPage

        icon.source: "qrc:/icons/search_white"
        icon.color: 'transparent'
        Layout.alignment: Qt.AlignRight
        Layout.rightMargin: -width / 3

        onClicked: {
          // prevent "SearchPageForm" to be pushed onto the stack multiple times
          if (!currentSearchPage
              || currentSearchPage != stackView.currentItem) {
            currentSearchPage = stackView.push("SearchPageForm.qml")
          }
        }
      }

      ToolButton {
        id: menuButton

        text: "\u22ee"

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

      onTriggered: {
        weatherApi.addCurrentLocationToFavourites()
        paneUndoFavLocation.show()
      }
    }

    onClosed: isOpen = false

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

    Column {
      anchors.fill: parent

      Label {
        id: lblColumnHeader

        text: qsTr("Favourite Locations")
        font.pointSize: Qt.application.font.pointSize
        font.bold: true

        width: parent.width
        height: 48
        leftPadding: 10
        verticalAlignment: Text.AlignVCenter
      }

      Repeater {
        model: weatherApi.favouriteLocations
        delegate: ItemDelegate {
          text: qsTr(modelData)
          font.pointSize: lblColumnHeader.font.pointSize
          width: parent.width

          onClicked: {
            weatherApi.setLocationByName(modelData)
            weatherApi.requestWeatherData()
            stackView.replace("WeatherForecastPageForm.qml")
            drawer.close()
          }
        }
      }
    }
  }

  StackView {
    id: stackView
    initialItem: "WeatherForecastPageForm.qml"
    anchors.fill: parent
  }

  Pane {
    id: paneUndoFavLocation

    opacity: stateMachine.running

    Behavior on opacity {
      NumberAnimation {
        easing.type: Easing.InOutQuad
        duration: 400}
    }

    Material.theme: Material.Dark

    height: 48
    width: parent.width
    anchors.bottom: parent.bottom

    RowLayout {
      anchors.topMargin: -11
      anchors.fill: parent

      Label {
        text: qsTr("Added %1 to Favourites").arg(stackView.currentItem.title)
      }

      Button {
        text: qsTr("Undo")
        flat: true
        Material.foreground: Material.Yellow

        Layout.alignment: Qt.AlignRight

        onClicked: {
          weatherApi.removeCurrentLocationFromFavourites()
          stateMachine.running = false
        }
      }
    }

    DSM.StateMachine {
        id: stateMachine

        initialState: hidden
        running: false

        DSM.State {
            id: hidden
            DSM.TimeoutTransition {
                targetState: shown
                timeout: 2500
            }
        }

        DSM.FinalState {
            id: shown
        }
    }

    function show() {
      stateMachine.running = true
    }
  }

  /**
   * @brief Replaces the WeatherForecastPageForm with the HomeForm in case the
   * app has been started for the first time to show the landing page.
   */
  function setFirstStartPage() {
    stackView.replace("HomeForm.ui.qml")
  }
}
