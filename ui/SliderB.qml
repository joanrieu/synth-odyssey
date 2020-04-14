import QtQuick 2.12
import Synth 1.0

Item {
    property string name
    property real min: 0
    property real max: 1
    property real power: 1

    property real value: {
        const scaled = Synth[name] - min
        const sign = Math.sign(scaled)
        return sign * Math.pow(sign * scaled / (max - min), 1 / power)
    }

    MouseArea {
        x: 16
        y: 32
        width: 16
        height: 160
        cursorShape: "PointingHandCursor"
        onMouseYChanged: {
            const slider = 0.5 - Math.min(1, Math.max(0, mouseY / height))
            const sign = Math.sign(slider)
            const scaled = sign * Math.pow(sign * slider, power) * (max - min)
            Synth[name] = min + scaled
        }
    }

    Rectangle {
        x: 22
        y: 22
        width: 4
        height: Math.min(button.y, 10 + 160 / 2)
        color: "black"
    }

    Rectangle {
        x: 22
        y: 22 + Math.max(button.y, 10 + 160 / 2)
        width: 4
        height: 36 + 160 - y
        color: "black"
    }

    Image {
        id: button
        source: "Button.png"
        scale: 0.5
        y: 10 + 160 * (0.5 - value)

        Behavior on y {
            NumberAnimation {
                duration: 40
            }
        }
    }
}
