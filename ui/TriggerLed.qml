import QtQuick 2.12
import Synth 1.0

Rectangle {
    width: 10
    height: 10
    color: "#2C2C2C"
    opacity: 0.7

    Connections {
        target: Synth
        onNoteOn: kbdTriggerBlink.running = true
    }

    SequentialAnimation on opacity {
        id: kbdTriggerBlink
        running: false

        NumberAnimation {
            from: 0.7
            to: 0
            duration: 100
        }
        NumberAnimation {
            from: 0
            to: 0.7
            duration: 100
        }
    }
}
