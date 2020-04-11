import QtQuick 2.12
import QtQuick.Controls 2.12
import Synth 1.0

MouseArea {
    anchors.fill: parent
    acceptedButtons: Qt.RightButton
    onClicked: menu.popup()

    Menu {
        id: menu
        modal: true

        Menu {
            title: "Presets"
            modal: true

            Menu {
                title: "Open"
                modal: true

                Repeater {
                    model: Synth.presetNames

                    MenuItem {
                        text: modelData
                        onTriggered: Synth.loadPreset(modelData)
                    }
                }
            }

            MenuItem {
                text: "Save"
                onTriggered: Synth.savePreset(Synth.presetName)
            }

            MenuItem {
                text: "Save As"
                onTriggered: {
                    presetNameField.text = Synth.presetName
                    saveAsDialog.open()
                }
            }
        }

        Menu {
            title: "MIDI in"
            modal: true
            width: 400

            Repeater {
                id: midiPorts

                MenuItem {
                    text: modelData
                    checkable: true
                    checked: Synth.midiPort === index
                    onTriggered: Synth.midiPort = Synth.midiPort !== index ? index : -1
                }
            }

            onAboutToShow: {
                midiPorts.model = Synth.midiPorts
            }
        }
    }

    Dialog {
        id: saveAsDialog
        title: "Save As"
        modal: true
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
