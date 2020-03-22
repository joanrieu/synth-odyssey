import QtQuick 2.12
import Synth 1.0

Item {
    property string name

    MouseArea {
        width: 8
        height: 29
        onClicked: Synth[name] = !Synth[name]
    }

    Rectangle {
        width: 8
        height: 12
        color: "black"
        opacity: !Synth[name]

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
        opacity: Synth[name]

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }
}
