import QtQuick 2.12
import Synth 1.0

Item {
    Repeater {
        model: 5

        Rectangle {
            x: index * 26
            width: 10
            height: 10
            color: "#2C2C2C"
            opacity: Synth.kbd_transpose === index - 2 ? 0 : 0.7

            MouseArea {
                anchors.fill: parent
                cursorShape: "PointingHandCursor"
                onClicked: Synth.kbd_transpose = index - 2
            }

            Behavior on opacity {
                NumberAnimation {
                    duration: 40
                }
            }
        }
    }
}
