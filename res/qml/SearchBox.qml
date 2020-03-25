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
/// \file   SearchBox.qml
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   08/02/2020
/// \brief  A styled search box
//============================================================================
import QtQuick 2.13
import QtQuick.Controls.Material 2.12

FocusScope {
  id: root

  property string placeholderText: "Type something..."
  signal textEdited(string text)
  signal cleared()

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
      root.focus = true
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
    onTextEdited: root.textEdited(text)
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
      onClicked: {
        input.clear()
        root.cleared()
        // show the keyboard again since it's likely the user wants to enter new text
        root.focus = true
        Qt.inputMethod.show()
      }
    }
  }

  states: State {
    name: "hasText"
    when: input.displayText !== ''
    PropertyChanges {
      target: placeholder
      opacity: 0
    }
    PropertyChanges {
      target: clear
      opacity: 1
    }
  }

  transitions: [
    Transition {
      from: ""
      to: "hasText"
      NumberAnimation {
        exclude: placeholder
        properties: "opacity"
      }
    },
    Transition {
      from: "hasText"
      to: ""
      NumberAnimation {
        properties: "opacity"
      }
    }
  ]
}
