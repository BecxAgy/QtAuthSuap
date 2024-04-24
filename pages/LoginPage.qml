import QtQuick 2.15
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

Item {
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
               login(usernameField.text, passwordField.text)
            }
        }
    }
}
