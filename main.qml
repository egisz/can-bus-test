import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    // Test fields for connectivity and values.
    property string status: "Not Connected"
    property int frames: 0
    property string filtering: "No"
    property int canId: 0
    property string payload: "None"
    property string deleted: "No"
    property string ended: "No"
    property string socket: "No"
    property int rpm: 0
    property int fuel: 0
    property int coolant: 0
    property int oil: 0

    visible: true
    width: 400
    height: 400
    title: qsTr("CAN Bus Testing")

    Text {
        id: txtStatus
        x: 8
        y: 131
        width: 181
        height: 23
        text: qsTr("Status: " + status)
        color: (status == "Not Connected") ? "red" : "green"
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12
    }

    Text {
        id: txtFrames
        x: 8
        y: 189
        width: 181
        height: 23
        text: qsTr("Frames: " + frames)
        color: (frames == 0) ? "red" : "green"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: txtPayload
        x: 8
        y: 247
        width: 181
        height: 23
        text: qsTr("Payload: " + payload)
        color: (payload == "None") ? "red" : "green"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: txtId
        x: 8
        y: 218
        width: 181
        height: 23
        text: qsTr("ID: " + canId)
        color: (canId == 0) ? "red" : "green"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: txtCanEnd
        x: 8
        y: 276
        width: 181
        height: 23
        text: qsTr("Ended: " + ended)
        color: (ended == "No") ? "red" : "green"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: txtFiltering
        x: 8
        y: 160
        width: 181
        height: 23
        text: qsTr("Filtering: " + filtering)
        color: (filtering == "No") ? "red" : "green"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: txtSocket
        x: 8
        y: 102
        width: 181
        height: 23
        text: qsTr("SocketCAN: " + socket)
        color: (socket == "No") ? "red" : "green"
        font.pixelSize: 12
        horizontalAlignment: Text.AlignLeft
    }

    Text {
        id: txtFuel
        x: 195
        y: 131
        width: 181
        height: 23
        color: (fuel == 0) ? "red" : "green"
        text: qsTr("Fuel: " + fuel)
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12
    }

    Text {
        id: txtOil
        x: 195
        y: 189
        width: 181
        height: 23
        color: (oil == 0) ? "red" : "green"
        text: qsTr("Oil: " + oil + "C")
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12
    }

    Text {
        id: txtCoolant
        x: 195
        y: 160
        width: 181
        height: 23
        color: (coolant == 0) ? "red" : "green"
        text: qsTr("Coolant: " + coolant + "C")
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12
    }

    Text {
        id: txtRpm
        x: 195
        y: 102
        width: 181
        height: 23
        color: (rpm == 0) ? "red" : "green"
        text: qsTr("Engine RPM: " + rpm)
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 12
    }
}
