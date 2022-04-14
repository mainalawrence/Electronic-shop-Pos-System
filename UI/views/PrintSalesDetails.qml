import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import Lib 1.0

//Date().getDay()+"/"+Date().getMonth()+"/"+Date().getFullYear(
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
        text: qsTr("Sales in Details\n"+timeday.toDateString())
        font.bold: true
        font.pixelSize:20
    }

        TableView{
            id:salesDetailstable
            anchors{
                left: parent.left
                right: parent.right
                top: title.bottom
                bottom: parent.bottom
            }

            property int col: 7
            model:masterController.ui_Sales
            TableViewColumn{
                role:'id'
                title: "Sale No"
                width:salesDetailstable.width/7
            }
            TableViewColumn{
                role:'name'
                title: "Item Name"
                width:salesDetailstable.width/7
            }
            TableViewColumn{
                role:'date'
                title: "Date"
                width:salesDetailstable.width/7
            }

            TableViewColumn{
                role:'cost'
                title: "Cost"
                width:salesDetailstable.width/7
            }
            TableViewColumn{
                role:'quantity'
                title: "Quantity"
                width:salesDetailstable.width/7
            }
            TableViewColumn{
                role:'total'
                title: "Total Cost"
                width:salesDetailstable.width/7
            }

            TableViewColumn{
                role:'profit'
                title: "Profit"
                width:salesDetailstable.width/7
            }

            style:TableViewStyle{
                headerDelegate:Frame{
                    anchors.bottomMargin:60
                    height:25
                    Text {
                        anchors.centerIn: parent
                        text: styleData.value
                    }
                }
                itemDelegate: Item {
                    height:40
                    Text {
                        anchors.centerIn: parent
                        color: styleData.textColor
                        elide: styleData.elideMode
                        text: styleData.value
                        font.bold: true
                        font.pixelSize:20
                    }
                }
            }

}

}
