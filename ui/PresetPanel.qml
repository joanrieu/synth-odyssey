import QtQuick 2.12
import Synth 1.0

Text {
    text: Synth.presetName + (Synth.presetDirty ? "*" : "")
    color: "white"
    font.pointSize: 12
    elide: Text.ElideRight
    horizontalAlignment: Text.AlignHCenter
}
