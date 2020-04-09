import QtQuick 2.12
import Synth 1.0

Item {
    property string name
    property real min: 0
    property real max: 1
    property real power: 1

    property real value: Math.pow((Synth[name] - min) / (max - min), 1 / power)

    MouseArea {
        x: 27
        y: 16
        width: 160
        height: 16
        cursorShape: "PointingHandCursor"
        onMouseXChanged: Synth[name] = min + Math.pow(Math.min(1, Math.max(0, mouseX / width)), power) * (max - min)
    }

    Rectangle {
        x: 18 + button.x
        y: 18
        width: 174 - button.x
        height: 4
        color: "black"
    }

    Image {
        id: button
        source: "Button.png"
        scale: 0.5
        x: 2 + 160 * value

        Behavior on x {
            NumberAnimation {
                duration: 40
            }
        }
    }
}
