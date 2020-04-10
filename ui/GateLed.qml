import QtQuick 2.12
import Synth 1.0

Rectangle {
    id: kbdGate
    width: 10
    height: 10
    color: "#2C2C2C"
    opacity: 0.7

    Connections {
        target: Synth
        onNoteOn: if (kbdGate.opacity != 0) kbdGateOn.running = true
        onNoteOff: kbdGateOff.running = true
    }

    NumberAnimation on opacity {
        id: kbdGateOn
        running: false
        from: 0.7
        to: 0
        duration: 100
    }

    NumberAnimation on opacity {
        id: kbdGateOff
        from: 0
        to: 0.7
        duration: 100
    }
}
