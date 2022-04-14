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
        text: qsTr("Most Sold Items\n"+timeday.toDateString())
        font.bold: true
        font.pixelSize: 18
    }
    TableView{
        id:mostsoldtable
         property int col:6
        anchors{
            left: parent.left
            right: parent.right
            top: title.bottom
            bottom: parent.bottom
        }
        height:parent.height-parent.height/5
        model:masterController.ui_MostsoldReport
        TableViewColumn{
            role:'id'
            title: "Receipt No"
            width: 50
        }
        TableViewColumn{
            role:'empname'
            title: "UserName"
            width:mostsoldtable.width/6
        }
        TableViewColumn{
            role:'paytype'
            title: "Sale Type"
             width:mostsoldtable.width/6
        }

        TableViewColumn{
            role:'date'
            title: "Sale Date"
            width:mostsoldtable.width/6
        }
        TableViewColumn{
            role:'total'
            title: "Total Cost"
            width:mostsoldtable.width/6
        }

        TableViewColumn{
            role:'profit'
            title: "Profit"
           width:mostsoldtable.width/6
        }

    }

}
