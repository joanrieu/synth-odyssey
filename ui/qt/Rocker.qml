import QtQuick 2.12

Item {
    property bool value: false

    MouseArea {
        width: 8
        height: 29
        onClicked: parent.value = !parent.value
    }

    Rectangle {
        id: mask1
        width: 8
        height: 12
        color: "black"
        opacity: parent.value ? 1 : 0

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }

    Rectangle {
        id: mask2
        y: 17
        width: 8
        height: 12
        color: "black"
        opacity: parent.value ? 0 : 1

        Behavior on opacity {
            NumberAnimation {
                duration: 200
            }
        }
    }
}
