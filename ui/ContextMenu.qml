import QtQuick 2.12
import QtQuick.Controls 2.12
import Synth 1.0

MouseArea {
    anchors.fill: parent
    acceptedButtons: Qt.RightButton
    onClicked: menu.popup()

    Menu {
        id: menu
        title: "Presets"

        Action {
            text: "Save"
            onTriggered: Synth.savePreset(Synth.presetName)
        }

        Action {
            text: "Save As"
            onTriggered: {
                presetNameField.text = Synth.presetName
                saveAsDialog.open()
            }
        }
    }

    Dialog {
        id: saveAsDialog
        title: "Save As"
        focus: true
        anchors.centerIn: parent
        standardButtons: Dialog.Save | Dialog.Cancel
        onAccepted: Synth.savePreset(presetNameField.text)

        TextField {
            id: presetNameField
            focus: true
            placeholderText: "Preset name"
        }
    }
}
