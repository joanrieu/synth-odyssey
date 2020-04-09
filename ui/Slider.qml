import QtQuick 2.12
import Synth 1.0

Item {
    property string name
    property real min: 0
    property real max: 1
    property real power: 1

    property real value: Math.pow((Synth[name] - min) / (max - min), 1 / power)

    MouseArea {
        x: 16
        y: 32
        width: 16
        height: 160
        cursorShape: "PointingHandCursor"
        onMouseYChanged: Synth[name] = min + Math.pow(1 - Math.min(1, Math.max(0, mouseY / height)), power) * (max - min)
    }

    Rectangle {
        x: 22
        y: 22
        width: 4
        height: button.y
        color: "black"
    }

    Image {
        id: button
        source: "Button.png"
        scale: 0.5
        y: 10 + 160 * (1 - value)

        Behavior on y {
            NumberAnimation {
                duration: 40
            }
        }
    }
}
