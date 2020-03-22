import QtQuick 2.12

Item {
    Rectangle {
        id: mask1
        width: 8
        height: 12
        color: "black"

        SequentialAnimation {
            running: true
            loops: Animation.Infinite

            NumberAnimation {
                target: mask1
                property: "opacity"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 0
                to: 1
            }

            NumberAnimation {
                target: mask1
                property: "opacity"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 1
                to: 0
            }
        }
    }

    Rectangle {
        id: mask2
        y: 17
        width: 8
        height: 12
        color: "black"

        SequentialAnimation {
            running: true
            loops: Animation.Infinite

            NumberAnimation {
                target: mask2
                property: "opacity"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 1
                to: 0
            }

            NumberAnimation {
                target: mask2
                property: "opacity"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 0
                to: 1
            }
        }
    }
}
