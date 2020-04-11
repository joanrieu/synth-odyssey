import QtQuick 2.12
import QtQuick.Controls 2.12
import Synth 1.0

Item {
    width: 157
    height: 40

    Item {
        anchors.top: parent.verticalCenter
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            text: Synth.presetName + (Synth.presetDirty ? "*" : "")

            anchors.fill: parent
            color: "white"
            font.pointSize: 12
            elide: Text.ElideRight
            horizontalAlignment: Text.AlignHCenter
        }
    }
}
