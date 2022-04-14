import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4


Item {
    id: root_recite
    anchors.fill: parent
    property alias phone_number:customerPhonetxt.text
    property alias customer_name:customernametxt.text
    property alias totalcost:totalCost_id.text
    //   property alias item_number:0
    property alias rendard_amount:rendered_id.text
    property alias change:change_id.text
    property alias transtype: lbltype_name.text
    property date currentDate: new Date()
    property int fontsize: 12

    Frame{
        id:printitem
        anchors.fill: parent
        rightPadding: parent.width/5
        background: Rectangle{
            border.color: 'transparent'
        }
        Item {
            id: header_id
            anchors.top: parent.top
            anchors.topMargin: parent.height/40
            anchors.horizontalCenter: parent.horizontalCenter

            Label{
                id:lblcompany_name
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                font.bold: true
                text:masterController.ui_companyName
                font.pixelSize:root_recite.fontsize
                font.family: 'Times New Roman'


            }
            Label{
                id:lblstreet_name
                anchors.top: lblcompany_name.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                font.bold: true
                text: masterController.ui_companyaAddress
                 font.pixelSize:root_recite.fontsize
                font.family: 'Times New Roman'
            }


            Label{
                id:comnumber
                anchors.top: lblstreet_name.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                text:masterController.ui_companyNumber
                 font.pixelSize:root_recite.fontsize
                font.bold: true
                font.family: 'Times New Roman'

            }
            Label{
                id:companyemial

                text:masterController.ui_companyEmail
                 font.pixelSize:root_recite.fontsize
                font.bold: true
                anchors.top: comnumber.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                font.family: 'Times New Roman'
            }


            Label{
                id:lbltype_name
                anchors.top: companyemial.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                font.bold: true
                text:""
               font.pixelSize:root_recite.fontsize
                anchors.topMargin:printitem.height/60
                font.family: 'Times New Roman'
            }

            Row{
                spacing: 20
                anchors.top:lbltype_name.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                Label{
                    id:customernametxt
                    text:"customer name"
                     font.pixelSize:root_recite.fontsize
                    font.bold: true
                    font.family: 'Times New Roman'

                }
                Label{
                    id:date_id
                    font.bold: true
                    text: root_recite.currentDate.toLocaleDateString(locale, Locale.ShortFormat)+'  '+ root_recite.currentDate.toLocaleTimeString(locale, Locale.ShortFormat)
                    font.pixelSize:root_recite.fontsize
                    anchors.topMargin:printitem.height/60
                    font.family: 'Times New Roman'
                }

                Label{
                    id:customerPhonetxt
                    text:"phone number"
                     font.pixelSize:root_recite.fontsize
                    font.bold: true
                    font.family: 'Times New Roman'

                }

            }

        }
        Rectangle{
            id:top_border
            anchors.top: header_id.bottom
            anchors.topMargin:printitem.height/10+(4*lblcompany_name.height)
            width:printitem.width
            height: 2
            border.color: 'gray'
            border.width: 2
        }
        Item {
            id: table_id
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: top_border.bottom
            height:24*view_.count
            anchors.topMargin: parent.height/40
            anchors.bottomMargin:50
            anchors.leftMargin: parent.width/3

            Rectangle{
                width: printitem.width
                height:15*view_.count+10
                ListView{
                    id:view_header
                    anchors{
                        top: parent.top
                        left: parent.left
                        right: parent.right
                    }
                    height:20
                    model:1
                    delegate: delegatetitle
                    clip: true

                }
                ListView{
                    id:view_
                    anchors{
                        top: view_header.bottom
                        left: parent.left
                        right: parent.right
                        bottomMargin: 5
                    }
                    height:view_.count*20
                    model:masterController.ui_Cart
                    delegate: delegate
                    clip: true

                }

            }

        }
        Component{
            id:delegate
            Rectangle{
                height:20
                width: parent.width
                Row{
                    anchors.fill: parent
                    spacing:parent.width/16
                    Text {
                        text: qsTr(model.name)
                        width:30
                         font.pixelSize:root_recite.fontsize
                        font.bold: true
                        font.family: 'Times New Roman'
                    }
                    Text {

                        text:model.cost
                        width:30
                        font.pixelSize:root_recite.fontsize
                        font.bold: true
                        font.family: 'Times New Roman'
                    }
                    Text {
                        text:model.quantity
                        width: 30
                         font.pixelSize:root_recite.fontsize
                        font.bold: true
                        font.family: 'Times New Roman'
                    }
                    Text {

                        text:model.total
                         font.pixelSize:root_recite.fontsize
                        font.bold: true
                        font.family: 'Times New Roman'
                    }
                }
            }
        }
        Component{
            id:delegatetitle
            Rectangle{
                height:25
                width: parent.width
                Row{
                    anchors.fill: parent
                    spacing: parent.width/16
                    Text {
                        width: 30
                        font.bold: true
                         font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                        text: qsTr("Name")
                    }
                    Text {
                        width: 30
                        font.bold: true
                       font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'

                        text: qsTr("Cost")
                    }
                    Text {
                        font.bold: true
                         font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                        text: qsTr(" Qnt")
                        width: 30
                    }
                    Text {
                        font.bold: true
                        font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                        text: qsTr("Total")
                        width:30
                    }
                }
            }
        }
        Rectangle{
            id:footer_border
            anchors.top: table_id.bottom
            anchors.topMargin:parent.height/10
            width:printitem.width
            height: 2
            border.color: 'gray'
            border.width: 2

        }
        Item {
            id: total_id
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: footer_border.bottom
            height: parent.height/16
            anchors.leftMargin: parent.width/2
            anchors.topMargin: parent.height/60
            Column{
                spacing: 5
                Row{
                    Label{
                        text: "GRAND TOTAL: "
                        font.bold: true
                         font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                    }
                    Label{
                        id:totalCost_id
                        text: ""
                        font.bold: true
                        font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                    }
                }
                Row{
                    Label{
                        text: "Cash:  "
                        font.bold: true
                        font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                    }

                    Label{
                        id:rendered_id
                        text:""
                        font.bold: true
                         font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                    }
                }
                Row{
                    Label{
                        text: "CHANGE:  "
                        font.bold: true
                       font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                    }
                    Label{
                        id:change_id
                        text: ""
                        font.bold: true
                         font.pixelSize:root_recite.fontsize
                        font.family: 'Times New Roman'
                    }
                }
            }
        }
    }
    Label{
        text:masterController.ui_companyapolicies
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: parent.height/3
        font.italic: true
        font.bold:true
        font.family: 'Times New Roman'
         font.pixelSize:root_recite.fontsize
    }

}
