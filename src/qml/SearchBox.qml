//============================================================================
/// \file   SearchBx.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   08/02/2020
/// \brief  A search box
//============================================================================
import QtQuick 2.13
import QtQuick.Controls.Material 2.12

FocusScope {
    id: focusScope

    property string placeholderText: "Type something..."
    signal textEdited(string text)

    width: 250
    height: 28

    Rectangle {
      width: parent.width
      height: parent.height
      radius: 10
      border.width: 2
      border.color: parent.activeFocus ? Material.accent : Material.foreground
    }

    Text {
        id: placeholder

        anchors.fill: parent
        anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter

        text: placeholderText
        color: "gray"
        font.italic: true
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
          focusScope.focus = true
          Qt.inputMethod.show()
        }
    }

    TextInput {
        id: input

        anchors {
          left: parent.left
          leftMargin: 8
          right: clear.left
          rightMargin: 8
          verticalCenter: parent.verticalCenter
        }
        focus: true
        selectByMouse: true
        onTextEdited: focusScope.textEdited(text)
    }

    Image {
        id: clear
        anchors {
          right: parent.right
          rightMargin: 8
          verticalCenter: parent.verticalCenter
        }
        source: "qrc:/icons/close"
        height: input.contentHeight
        fillMode: Image.PreserveAspectFit
        opacity: 0

        MouseArea {
            anchors.fill: parent
            onClicked: input.clear()
        }
    }

    states: State {
        name: "hasText"; when: input.displayText !== ''
        PropertyChanges { target: placeholder; opacity: 0 }
        PropertyChanges { target: clear; opacity: 1 }
    }

    transitions: [
        Transition {
            from: ""; to: "hasText"
            NumberAnimation { exclude: placeholder; properties: "opacity" }
        },
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}
