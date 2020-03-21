import QtQuick 2.12

Item {
    height: 180

    Rectangle {
        x: 22
        y: 22
        width: 4
        height: button.y
        color: "black"
    }

    Image {
        id: button
        source: "Button.png"
        scale: 0.5

        SequentialAnimation {
            running: true
            loops: Animation.Infinite

            NumberAnimation {
                target: button
                property: "y"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 10
                to: 170
            }

            NumberAnimation {
                target: button
                property: "y"
                duration: 1000
                easing.type: Easing.InOutQuad
                from: 170
                to: 10
            }
        }
    }
}
