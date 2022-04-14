import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2
import Lib 1.0

Item {
    id:root
    property string category:''
    property string rname
    property int rquantity
    property string rcategory
    property int rprice
    property string rid
    property string rcname
    property string rcid
    property int wholesale
    Button{
        x:5
        y:5
        text: "Home"
        onClicked: {
            masterController.ui_navigation.goCreatedashboardView()
        }
    }
    Item{
        id:add_id
        height: 50
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            leftMargin:root.width/60
            rightMargin: root.width/60
            topMargin: 20
        }
        Row{
            spacing: 10
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin:parent.width/20

            Button{
                id:additem_id
                Text{
                    anchors.centerIn: parent
                    color: 'white'
                    text: "New Item"
                    font.bold: true
                }
                style: ButtonStyle {

                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 30
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#117a8b"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                            GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                        }
                    }
                }
                onClicked: {
                    additem_dialog_id.open()
                }
            }
            Button{
                id:importitem_id
                visible: false


                Text{
                    anchors.centerIn: parent
                    color: 'white'
                    text: "CSV import"
                    font.bold: true
                }
                style: ButtonStyle {

                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 30
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                            GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                        }
                    }
                }
                onClicked: {

                }
            }


        }
    }

    Frame{
        id:search_id
        height: 50
        anchors{
            left: parent.left
            right: parent.right
            top: add_id.bottom
            leftMargin:root.width/60
            rightMargin: root.width/60
            bottomMargin: 20
        }


        Rectangle{
            id:serch_id
            border.color:'gray'
            radius: 4
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: export_id.left
            anchors.rightMargin: 10
            width: 200
            height: 30
            focus: true
            TextInput{
                id:serch_text
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                text: ""
                focus: true
                font.bold: true
                cursorVisible: true
                onTextChanged: {
                    masterController.onStock_search(serch_text.text)
                    returnstable.model=masterController.ui_Stocks
                }


            }

        }
        Button{
            id:export_id
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin:parent.width/30

            Text{
                anchors.centerIn: parent
                color: 'white'
                text: "CSV export"
                font.bold: true
            }
            style: ButtonStyle {
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 30
                    border.width: control.activeFocus ? 2 : 1
                    border.color: "#888"
                    radius: 4
                    gradient: Gradient {
                        GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                        GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                    }
                }
            }
            onClicked: {
                masterController.onExport_to_csv("stock","")
            }

        }

    }
    Frame{
        id:table_id
        property int col:7
        anchors{
            left: parent.left
            right: parent.right
            top: search_id.bottom
            bottom: parent.bottom
            topMargin:5
        }
        Item {
            id: stock_table
            anchors.fill: parent
            TableView{
                id:returnstable
                anchors.fill: parent
                TableViewColumn{
                    role:'id'
                    title: "ReciteNo"
                    width: returnstable.width/table_id.col
                }
                TableViewColumn{
                    role:'name'
                    title: "item Name"
                    width: returnstable.width/table_id.col
                }
                TableViewColumn{
                    role:'amount'
                    title: "Amount if items"
                    width: returnstable.width/table_id.col
                }
                TableViewColumn{
                    role:'wholesale'
                    title: "WholeSale"
                    width: returnstable.width/table_id.col
                }

                TableViewColumn{
                    role:'price'
                    title: "Cost per Item"
                    width: returnstable.width/table_id.col
                }

                TableViewColumn{
                    role:'category'
                    title: "Item Category"
                    width: returnstable.width/table_id.col
                }

                TableViewColumn{
                    id:edit_id
                    delegate: Rectangle{
                        color: "transparent"
                        radius: 50
                        Row{
                            spacing: 5
                            Button{
                                width:30
                                height: 15
                                text: "X"
                                onClicked: {
                                    masterController.onRemove_ItemRow(Number(model.id))
                                    masterController.onReload()
                                }
                            }
                            Button{
                                text: "Edit"
                                height: 5*3
                                onClicked: {
                                    root.rname=model.name
                                    root.rquantity=model.amount
                                    root.rcategory=model.category
                                    root.rprice=model.price
                                    root.rid=model.id
                                    root.wholesale=model.wholesale
                                    updateitem_dialog_id.open()
                                }

                            }
                        }
                    }
                }
                model:masterController.ui_Stocks
                style:TableViewStyle{

                    headerDelegate:Frame{
                        height:30
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
        }


    }
    Dialog{
        id:additem_dialog_id
        modality:Qt.WindowModal
        title: "Add Item"

        contentItem: Rectangle{
            implicitHeight: root.height/1.5
            implicitWidth: root.width/3
            IAdditem{
                anchors.fill: parent

            }
        }

    }
    Dialog{
        id:updateitem_dialog_id
        modality:Qt.WindowModal
        title: "Add Item"

        contentItem: Rectangle{
            implicitHeight: root.height/1.5
            implicitWidth: root.width/3
            Update_item{
                anchors.fill: parent
                name:root.rname
                quantity:root.rquantity

                price: root.rprice
                upid:root.rid
                wholesale:root.wholesale
                category:root.rcategory

                onSubmitclicked:{
                    masterController.onReload()

                }
            }
        }

    }
    Dialog{
        id:addcategoly_dialog_id
        modality:Qt.WindowModal
        title: "Add Category"
        contentItem:Frame{
            anchors.margins: 50
            implicitHeight:  root.height/2
            implicitWidth: root.width/4
            padding:20

            Column{
                spacing: 20
                anchors.fill: parent
                Column{
                    spacing: 5
                    height: parent.width/2
                    width: parent.width
                    Label{
                        text: "Enter Category"
                        width: parent.width
                        height:20

                    }
                    TextField{
                        id:categorytxt
                        focus: true
                        text: ""
                        onTextChanged:root.category=categorytxt.text
                        width: parent.width
                        height: 40

                    }
                }
                Row{
                    spacing:parent.width-(submit_id.width*2)
                    Button{
                        id:submit_id
                        Text{
                            anchors.centerIn: parent
                            color: 'white'
                            text:  "Discard "
                            font.bold: true
                        }
                        style: ButtonStyle {

                            background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 30
                                border.width: control.activeFocus ? 2 : 1
                                border.color: "#28a745"
                                radius: 4
                                gradient: Gradient {
                                    GradientStop { position: 0 ; color: control.pressed ?"#20bb44" : "#28a745" }
                                    GradientStop { position: 1 ; color: control.pressed ?"#20bb44" : "#28a745" }
                                }
                            }
                        }
                        onClicked: {

                            categorytxt.text="";
                            addcategoly_dialog_id.close()
                        }
                    }
                    Button{

                        Text{
                            anchors.centerIn: parent
                            color: 'white'
                            text:  "Submit"
                            font.bold: true
                        }
                        style: ButtonStyle {

                            background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 30
                                border.width: control.activeFocus ? 2 : 1
                                border.color: "#28a745"
                                radius: 4
                                gradient: Gradient {
                                    GradientStop { position: 0 ; color: control.pressed ?"#20bb44" : "#28a745" }
                                    GradientStop { position: 1 ; color: control.pressed ?"#20bb44" : "#28a745" }
                                }
                            }
                        }
                        onClicked: {

                            masterController.onAddcategry(root.category.toString())
                            addcategoly_dialog_id.close()
                            categorytxt.text="";

                        }
                    }
                }
            }
        }

    }

}
