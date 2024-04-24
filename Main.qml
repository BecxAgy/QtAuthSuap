import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material
import QtAuthSuap

ApplicationWindow {
    visible: true

    header: ToolBar {
        Material.background: 'green'
        RowLayout {
            anchors.fill: parent
            Label {
                text: "Emile"
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }
            ToolButton {
                text: qsTr("⋮")
                onClicked: menu.open()
            }
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: 300

        TextField {
            id: usernameField
            placeholderText: "User"
            Layout.fillWidth: true
        }

        TextField {
            id: passwordField
            placeholderText: "Password"
            echoMode: TextInput.Password
            Layout.fillWidth: true
        }

        Button {
            text: "Login"
            onClicked: {
                NetworkManager.login(usernameField.text, passwordField.text);
                console.log("deu bom??")
            }
        }
    }
}
