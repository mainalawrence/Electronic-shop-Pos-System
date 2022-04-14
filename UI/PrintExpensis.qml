import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import Lib 1.0


Item {
    id:root
    property date timeday:new Date()
    anchors.fill: parent
        Text {
            id: title
            anchors{
                topMargin: 5
                horizontalCenter: parent.horizontalCenter
                top: parent.top
            }
            text: qsTr("Expensis\n"+timeday.toDateString())
            font.bold: true
            font.pixelSize: 18
        }
        TableView{
            id:expensisitable
            anchors{
                left: parent.left
                right: parent.right
                top: title.bottom
                bottom: parent.bottom
            }
            model:masterController.ui_Expensis
            TableViewColumn{
                role:'id'
                title: " No"
                width: expensisitable.width/4-40
            }
            TableViewColumn{
                role:'details'
                title: "DETAILS"
                width: expensisitable.width/4
            }
            TableViewColumn{
                role:'date'
                title: "DATE"
                width: expensisitable.width/4
            }
            TableViewColumn{
                role:'amount'
                title: "AMOUNT"
               width: expensisitable.width/4
            }
        }

}
