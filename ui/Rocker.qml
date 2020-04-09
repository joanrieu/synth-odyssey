import QtQuick 2.12
import Synth 1.0

Item {
    property string name
    property bool value: Synth[name]

    MouseArea {
        width: 8
        height: 29
        onClicked: Synth[name] = !value
        cursorShape: "PointingHandCursor"
    }

    Rectangle {
        width: 8
        height: 12
        color: "black"
        opacity: !value

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    Rectangle {
        y: 17
        width: 8
        height: 12
        color: "black"
        opacity: value

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }
}
