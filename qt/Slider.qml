import QtQuick 2.12
import Synth 1.0

Item {
    property string name
    property real value: Synth[name]

    MouseArea {
        x: 16
        y: 32
        width: 16
        height: 160
        cursorShape: "PointingHandCursor"
        onMouseYChanged: Synth[name] = 1 - Math.min(1, Math.max(0, mouseY / this.height))
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
