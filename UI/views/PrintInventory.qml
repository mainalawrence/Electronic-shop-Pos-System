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
            text: qsTr("Inventory\n"+timeday.toDateString())
            font.bold: true
            font.pixelSize: 18
        }
        TableView{
            id:inventorytable

            anchors{
                left: parent.left
                right: parent.right
                top: title.bottom
                bottom: parent.bottom
            }
            model:masterController.ui_Inventory
            TableViewColumn{
                role:'id'
                title: "Item Id"
                 width:inventorytable.width/6
            }
            TableViewColumn{
                role:'name'
                title: "Item Name"
                  width:inventorytable.width/6
            }
            TableViewColumn{
                role:'category'
                title: "Category"
                  width:inventorytable.width/6
            }
            TableViewColumn{
                role:'amount'
                title: "Quantity"
                 width:inventorytable.width/6
            }
            TableViewColumn{
                role:'price'
                title: "Item Price"
                 width:inventorytable.width/6
            }
            TableViewColumn{
                role:'profit'
                title: "Item Total Cost"
                width:inventorytable.width/6
            }

        }

}
