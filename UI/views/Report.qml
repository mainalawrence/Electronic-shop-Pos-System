import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.4
import Lib 1.0

Item {
    id: rootreport
    Button{
        x:5;y:5
        text: "Home"
        onClicked: {
            masterController.ui_navigation.goCreatedashboardView()
        }
    }


    Item{
        id: root_sale_id
        anchors.fill: parent
        property int col:6
        property string salestype
        TabView {
            id: frame
            anchors.fill: parent
            anchors.margins: 4
            anchors.topMargin: 30
            Tab {
                title: "SALES "
                Rectangle{
                    id:sales_id
                    anchors.fill:parent
                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }

                    SubHeaderReport{
                        id:subh_sales
                        height: 50
                        width: parent.width
                        root_id: "sales"
                        searchtxtvisible:true
                    }
                    Rectangle {
                        id:sales_tabler_id
                        color:"transparent"
                        anchors.top: subh_sales.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/60
                        TableView{
                            id:salestable
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height:parent.height-parent.height/5

                            model:masterController.ui_SalesReport
                            TableViewColumn{
                                role:'id'
                                title: "Receipt No"
                                width: salestable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'empname'
                                title: "UserName"
                                width: salestable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'paytype'
                                title: "Sale Type"
                                width: salestable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'date'
                                title: "Sale Date"
                                width: salestable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'total'
                                title: "Total Cost"
                                width: salestable.width/root_sale_id.col
                            }

                            TableViewColumn{
                                role:'profit'
                                title: "Profit"
                                width: salestable.width/root_sale_id.col
                            }
                            style:TableViewStyle{
                                headerDelegate:Frame{
                                    height:25
                                    Text {
                                        anchors.centerIn: parent
                                        text: styleData.value
                                    }
                                }

                                itemDelegate: Item {
                                    height: 30
                                    Text {
                                        anchors.centerIn: parent
                                        color: styleData.textColor
                                        elide: styleData.elideMode
                                        text: styleData.value
                                    }
                                }
                            }
                        }
                        Rectangle{
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: salestable.bottom
                                bottom: parent.bottom
                                leftMargin: parent.width/2.5
                            }
                            height: 20

                            Column{
                                spacing: 2
                                anchors.fill: parent
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Transaction: "+masterController.ui_mTotalItem
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Cost: "+masterController.ui_mGrandTotal
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Profit: "+masterController.ui_mProfit
                                }
                            }

                        }


                    }
                }
            }
            Tab { title: "RETURNS  "
                Rectangle{
                    id:returns_id
                    anchors.fill:parent

                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }

                    SubHeaderReport{
                        id:subh_returns
                        height: 50
                        width: parent.width
                        root_id: "returns"
                        searchtxtvisible:true
                    }
                    Rectangle {
                        id:returns_tabler_id
                        color:"transparent"
                        anchors.top: subh_returns.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/60
                        TableView{
                            id:returntable
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height:parent.height-parent.height/5
                            model:masterController.ui_ReturnReport
                            TableViewColumn{
                                role:'id'
                                title: "Receipt No"
                                width: returntable.width/root_sale_id.col-20
                            }
                            TableViewColumn{
                                role:'empname'
                                title: "UserName"
                                width: returntable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'paytype'
                                title: "Sale Type"
                                width: returntable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'date'
                                title: "Sale Date"
                                width: returntable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'total'
                                title: "Total Cost"
                                width: returntable.width/root_sale_id.col
                            }

                            TableViewColumn{
                                role:'profit'
                                title: "Profit"
                                width: returntable.width/root_sale_id.col
                            }
                            style:TableViewStyle{
                                headerDelegate:Frame{
                                    height:25
                                    Text {
                                        anchors.centerIn: parent
                                        text: styleData.value
                                    }
                                }

                                itemDelegate: Item {
                                    height: 30
                                    Text {
                                        anchors.centerIn: parent
                                        color: styleData.textColor
                                        elide: styleData.elideMode
                                        text: styleData.value
                                    }
                                }
                            }

                        }
                        Rectangle{
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: returntable.bottom
                                bottom: parent.bottom
                                leftMargin: parent.width/2.5
                            }
                            height: 20

                            Column{
                                spacing: 2
                                anchors.fill: parent
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Transaction: "+masterController.ui_mReturnTotalItem
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Cost Returned: "+masterController.ui_mReturnGrandTotal
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Profit Returned: "+masterController.ui_mReturnProfit
                                }
                            }

                        }

                    }
                }
            }
            //most dold item
            Tab { title: "MOST SOLD  "
                Rectangle{
                    id:mostsold_id
                    anchors.fill:parent
                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }
                    SubHeaderReport{
                        id:mostsold_header_id
                        height: 50
                        width: parent.width
                        root_id: "most sold"
                        searchtxtvisible:true
                    }
                    Rectangle {
                        id:stdsold_tabler_id
                        color:"transparent"
                        anchors.top: mostsold_header_id.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/60
                        TableView{
                            id:mostsoldtable
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height:parent.height-parent.height/5
                            model:masterController.ui_MostsoldReport
                            TableViewColumn{
                                role:'id'
                                title: "Receipt No"
                                width: mostsoldtable.width/root_sale_id.col-20
                            }
                            TableViewColumn{
                                role:'empname'
                                title: "UserName"
                                width: mostsoldtable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'paytype'
                                title: "Sale Type"
                                width: mostsoldtable.width/root_sale_id.col
                            }

                            TableViewColumn{
                                role:'date'
                                title: "Sale Date"
                                width: mostsoldtable.width/root_sale_id.col
                            }
                            TableViewColumn{
                                role:'total'
                                title: "Total Cost"
                                width: mostsoldtable.width/root_sale_id.col
                            }

                            TableViewColumn{
                                role:'profit'
                                title: "Profit"
                                width: mostsoldtable.width/root_sale_id.col
                            }
                            style:TableViewStyle{
                                headerDelegate:Frame{
                                    height:25
                                    Text {
                                        anchors.centerIn: parent
                                        text: styleData.value
                                    }
                                }

                                itemDelegate: Item {
                                    height: 30
                                    Text {
                                        anchors.centerIn: parent
                                        color: styleData.textColor
                                        elide: styleData.elideMode
                                        text: styleData.value
                                    }
                                }
                            }

                        }
                        Rectangle{
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: mostsoldtable.bottom
                                bottom: parent.bottom
                                leftMargin: parent.width/2.5
                            }
                            height: 20

                            Column{
                                spacing: 2
                                anchors.fill: parent
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Transaction: "+masterController.ui_mMstTotalItem
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Cost: "+masterController.ui_mMstGrandTotal
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Profit: "+masterController.ui_mMstProfit
                                }
                            }

                        }

                    }
                }
            }

            Tab { title: "INVENTORY   "
                Rectangle{
                    id:inverntory_id
                    property int col:6
                    anchors.fill:parent
                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }
                    SubHeaderReport{
                        id:inventory_header_id
                        height: 50
                        width: parent.width
                        root_id: "inventory"
                        searchtxtvisible:false
                    }
                    Rectangle {
                        id:inventory_tabler_id
                        color:"transparent"
                        anchors.top: inventory_header_id.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/60
                        TableView{
                            id:inventorytable
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height:parent.height-parent.height/5
                            model:masterController.ui_Inventory
                            TableViewColumn{
                                role:'id'
                                title: "Item Id"
                                width: inventorytable.width/inverntory_id.col
                            }
                            TableViewColumn{
                                role:'name'
                                title: "Item Name"
                                width: inventorytable.width/inverntory_id.col
                            }
                            TableViewColumn{
                                role:'category'
                                title: "Category"
                                width: inventorytable.width/inverntory_id.col
                            }
                            TableViewColumn{
                                role:'amount'
                                title: "Quantity"
                                width: inventorytable.width/inverntory_id.col
                            }

                            TableViewColumn{
                                role:'price'
                                title: "Item Price"
                                width: inventorytable.width/inverntory_id.col
                            }
                            TableViewColumn{
                                role:'profit'
                                title: "Item Total Cost"
                                width: inventorytable.width/inverntory_id.col
                            }
                            style:TableViewStyle{
                                headerDelegate:Frame{
                                    height:25
                                    Text {
                                        anchors.centerIn: parent
                                        text: styleData.value
                                    }
                                }

                                itemDelegate: Item {
                                    height: 30
                                    Text {
                                        anchors.centerIn: parent
                                        color: styleData.textColor
                                        elide: styleData.elideMode
                                        text: styleData.value
                                    }
                                }
                            }

                        }
                        Rectangle{
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: inventorytable.bottom
                                bottom: parent.bottom
                                leftMargin: parent.width/2.5
                            }
                            height: 20

                            Column{
                                spacing: 2
                                anchors.fill: parent
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Items: "+masterController.ui_InventoryAmount
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Totoal Cost: "+masterController.ui_InventoryTotal
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Profit: "+masterController.ui_InventoryDProfit
                                }
                            }

                        }

                    }
                }
            }

            Tab { title: "SALES In DETAILS  "
                Rectangle{
                    id:salesDetails_id
                    anchors.fill:parent
                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }
                    SubHeaderReport{
                        id:salesDetailsy_header_id
                        height: 50
                        width: parent.width
                        root_id: "saleDetails"
                        searchtxtvisible:true
                    }
                    Rectangle {
                        id:salesDetails_tabler_id
                        color:"transparent"
                        anchors.top: salesDetailsy_header_id.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/60
                        property int col: 7
                        TableView{
                            id:salesDetailstable
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height:parent.height-parent.height/5
                            model:masterController.ui_Sales
                            TableViewColumn{
                                role:'id'
                                title: "Sale No"
                                width: salesDetailstable.width/salesDetails_tabler_id.col-20
                            }
                            TableViewColumn{
                                role:'name'
                                title: "Item Name"
                                width: salesDetailstable.width/salesDetails_tabler_id.col
                            }
                            TableViewColumn{
                                role:'date'
                                title: "Date"
                                width: salesDetailstable.width/salesDetails_tabler_id.col
                            }

                            TableViewColumn{
                                role:'cost'
                                title: "Cost"
                                width: salesDetailstable.width/salesDetails_tabler_id.col
                            }
                            TableViewColumn{
                                role:'quantity'
                                title: "Quantity"
                                width: salesDetailstable.width/salesDetails_tabler_id.col
                            }
                            TableViewColumn{
                                role:'total'
                                title: "Total Cost"
                                width: salesDetailstable.width/salesDetails_tabler_id.col
                            }

                            TableViewColumn{
                                role:'profit'
                                title: "Profit"
                                width: salesDetailstable.width/salesDetails_tabler_id.col
                            }
                            style:TableViewStyle{
                                headerDelegate:Frame{
                                    height:25
                                    Text {
                                        anchors.centerIn: parent
                                        text: styleData.value
                                    }
                                }

                                itemDelegate: Item {
                                    height: 30
                                    Text {
                                        anchors.centerIn: parent
                                        color: styleData.textColor
                                        elide: styleData.elideMode
                                        text: styleData.value
                                    }
                                }
                            }

                        }
                        Rectangle{
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: salesDetailstable.bottom
                                bottom: parent.bottom
                                leftMargin: parent.width/2.5
                            }
                            height: 20

                            Column{
                                spacing: 2
                                anchors.fill: parent
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Transaction: "+masterController.ui_SaleDAmount
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Cost: "+masterController.ui_SaleDTotal
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Profit: "+masterController.ui_SaleDProfit
                                }
                            }

                        }
                    }
                }

            }
            Tab { title: "EXPENSIS  "
                Rectangle{
                    id:expensis
                    anchors.fill:parent
                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }

                    SubHeaderReport{
                        id:expens
                        height: 50
                        width: parent.width
                        root_id: "Expensis"
                        searchtxtvisible:true
                    }
                    Rectangle {
                        id:expensis_tabler_id
                        color:"transparent"
                        anchors.top: expens.bottom;
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: parent.height/60
                        property int col: 5
                        TableView{
                            id:expensisitable
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }
                            height:parent.height-parent.height/5
                            model:masterController.ui_Expensis
                            TableViewColumn{
                                role:'id'
                                title: " No"
                                width: expensisitable.width/expensis_tabler_id.col-20
                            }
                            TableViewColumn{
                                role:'description'
                                title: "DETAILS"
                                width: expensisitable.width/expensis_tabler_id.col
                            }
                            TableViewColumn{
                                role:'employee'
                                title: "NAME"
                                width: expensisitable.width/expensis_tabler_id.col
                            }
                            TableViewColumn{
                                role:'date'
                                title: "DATE"
                                width: expensisitable.width/expensis_tabler_id.col
                            }

                            TableViewColumn{
                                role:'amount'
                                title: "AMOUNT"
                                width: expensisitable.width/expensis_tabler_id.col
                            }

                            style:TableViewStyle{
                                headerDelegate:Frame{
                                    height:25
                                    Text {
                                        anchors.centerIn: parent
                                        text: styleData.value
                                    }
                                }

                                itemDelegate: Item {
                                    height: 30
                                    Text {
                                        anchors.centerIn: parent
                                        color: styleData.textColor
                                        elide: styleData.elideMode
                                        text: styleData.value
                                    }
                                }
                            }

                        }
                        Rectangle{
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: expensisitable.bottom
                                bottom: parent.bottom
                                leftMargin: parent.width/2.5
                            }
                            height: 20

                            Column{
                                spacing: 2
                                anchors.fill: parent
                                Label{
                                    font.pixelSize: 18
                                    text:"Total Transaction: "+masterController.ui_ExpenisiTransaction
                                }
                                Label{
                                    font.pixelSize: 18
                                    text:"TOTAL AMOUNT: "+masterController.ui_totalexpensis
                                }

                            }

                        }
                    }
                }
            }
            Tab { title: " PROFIT &LOSS A/C"
                Rectangle{
                    id:profitadloss
                    anchors.fill:parent
                    anchors{
                        leftMargin:parent.width/60
                        rightMargin:parent.width/60
                        topMargin: parent.height/60
                    }
                    SubHeaderReport{
                        id:profitloss
                        height: 50
                        width: parent.width
                        root_id: "ProfitLoss"
                        searchtxtvisible:true
                    }

                Frame{
                   anchors.centerIn: parent
                   height: 500
                   width: parent.width/2-100

                  Column{
                      spacing: 20
                      anchors.fill: parent
                      Label{
                          text: "Date: "+ new Date().toISOString()
                         height:30
                          anchors.horizontalCenter: parent.horizontalCenter
                          font.pixelSize: 20

                      }
                      Rectangle{
                          width:parent.width
                          height:2;
                          border.color: "black"
                          border.width:2

                      }

                      Label{
                           font.pixelSize: 16
                          text: "CURRENT STOCK :"+masterController.ui_PLInventory
                      }
                      Label{
                           font.pixelSize: 16
                          text: "TOTAL SALES   :"+masterController.ui_mPLSales
                      }
                      Label{
                           font.pixelSize: 16
                          text: "TOTAL DISCOUNT  :"+masterController.ui_PLDiscount
                      }
                      Label{
                          font.pixelSize: 16
                         text: "TOTAL EXPENSIS   :"+masterController.ui_mPLExpenisi
                     }
                      Label{
                          font.pixelSize: 18
                          text: "TOTAL PROFIT   :"+masterController.ui_mPLProfits
                      }

                  }
                }}
            }
            style: TabViewStyle {
                frameOverlap: 1
                tabsAlignment : Qt.AlignHCenter
                tabsMovable:false
                tab: Rectangle {
                    color: "transparent"
                    border.color:  "transparent"
                    implicitWidth: Math.max(text.width + 4, 80)
                    implicitHeight: 30
                    anchors.leftMargin:20
                    radius: 4
                    Text {
                        id: text
                        font.pixelSize: 18
                        anchors.centerIn: parent
                        text: styleData.title
                        font.bold: true
                        color: styleData.selected ? "skyblue" : "#20c997"
                    }
                }
                frame: Rectangle { }
            }
        }
    }

}
