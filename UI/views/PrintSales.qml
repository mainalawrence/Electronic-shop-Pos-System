import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import Lib 1.0

Item {

    id:root
    anchors.fill: parent
    property date timeday:new Date()
    Text {
        id: title
        anchors{
            topMargin: 5
            horizontalCenter: parent.horizontalCenter
            top: parent.top
        }
        text: qsTr("Sales\n"+timeday.toDateString())
        font.bold: true
        font.pixelSize: 18
    }

    TableView{
        id:salestable
        anchors{
            left: parent.left
            right: parent.right
            top: title.bottom
            bottom: parent.bottom
        }


        model:masterController.ui_SalesReport
        TableViewColumn{
            role:'id'
            title: "Receipt No"
            width:100
        }
        TableViewColumn{
            role:'empname'
            title: "UserName"
            width:100
        }
        TableViewColumn{
            role:'paytype'
            title: "Sale Type"
              width:100
        }
        TableViewColumn{
            role:'date'
            title: "Sale Date"
            width:100
        }
        TableViewColumn{
            role:'total'
            title: "Total Cost"
              width:100
        }

        TableViewColumn{
            visible: masterController.ui_visiblebnt
            role:'profit'
            title: "Profit"
             width:100
        }


    }

}
