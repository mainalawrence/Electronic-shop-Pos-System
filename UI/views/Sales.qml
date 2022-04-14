﻿import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Controls 1.2

Item {
    id:root
    //the layer for back home
    Button{
        x:5
        visible:masterController.ui_visiblebnt
        y:5
        text: "Home"
        onClicked: {
            masterController.ui_navigation.goCreatedashboardView()
        }
    }
    property bool selectCat: false
    Item{
        id:topid
        property int change:tended-totalcost
        property int totalcost:masterController.ui_Cart.ui_Grandtotal
        property int amount: masterController.ui_Cart.ui_Amount
        property int chnge:masterController.ui_Cart.ui_Grandtotal
        property int tended:masterController.ui_Cart.ui_Tendered
        property int discount: masterController.ui_Cart.ui_Discount
        property bool enable:false
        property int col:5

        anchors.top: parent.top;
        anchors.left: parent.left
        anchors.right: salep_id.left
        anchors.bottom: parent.bottom
        anchors.leftMargin:10
        anchors.rightMargin: 10
        anchors.topMargin:40
        height: 200
        Frame{
            id:rootcategory_id
            anchors.top: parent.top;
            anchors.left: parent.left
            anchors.right: parent.right
            padding:20
            // height: parent.height/8
            background:Rectangle {
                color: "gray"
            }

            Row{
                spacing: 50
                Label{
                    text: "Search Product"
                    font.bold: true
                    font.pixelSize: 13
                }
                Rectangle{
                    id:serch_id
                    width: 250
                    height: 30
                    focus: true
                    TextInput{
                        id:serch_text
                        focus: true
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        text: ""
                        font.bold: true
                        cursorVisible: true
                        onTextChanged: {
                            if(serch_text.text!==''){
                                root.selectCat=true
                                masterController.onAddtoCart(serch_text.text)
                                selectmodel.model=''
                                selectmodel.model=masterController.ui_Search_Stock_to_Cart
                            }
                            else{
                                root.selectCat=false
                                serch_text.text=''
                                selectmodel.model=''
                                selectmodel.model=masterController.ui_Search_Stock_to_Cart

                            }
                        }

                    }

                }
                ComboBox{
                    id:type_receit_id
                    model:["SALES","RETURN"]


                    implicitWidth: 130
                    implicitHeight: 30
                    style: ComboBoxStyle{
                        background:Rectangle{
                            color:"skyblue"
                            radius: 5
                        }
                        textColor: 'black'
                        font.bold: true
                    }
                }
Label{
    id:saletype
    text:type_receit_id.currentText
    visible: false
}
                Button{
                    id:add_btn
                    text: "CASH OUT"
                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 80
                            implicitHeight: 30
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#17a2b8"
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
                    id:suspend_btn
                    text: "Daily Report"
                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 100
                            implicitHeight: 30
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#17a2b8"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                                GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                            }
                        }
                    }
                    onClicked: {
                        dailyreport.open()
                    }
                }
                Button{
                    id:stock_bnt
                    text: "STOCK"
                    style: ButtonStyle {
                        background: Rectangle {
                            implicitWidth: 80
                            implicitHeight: 30
                            border.width: control.activeFocus ? 2 : 1
                            border.color: "#17a2b8"
                            radius: 4
                            gradient: Gradient {
                                GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                                GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                            }
                        }
                    }
                    onClicked: {
                        viewstock.open()
                    }
                }
            }
        }
        ListView{
            id:selectmodel
            visible: root.selectCat
            x:serch_id.x+serch_id.width/12
            y:serch_id.y+60
            width: serch_id.width;height:serch_id.height*selectmodel.count
            model:masterController.ui_Search_Stock_to_Cart
            delegate:delegateid
        }
        Component{
            id:delegateid
            Rectangle {
                id:comRect
                height:serch_id.height
                width:serch_id.width
                radius: 5
                Text {
                    anchors.fill: parent
                    anchors.leftMargin: 20
                    font.pixelSize: 16
                    text: qsTr(model.name)
                }
                MouseArea{
                    id:mousearea_id
                    anchors.fill: parent
                    onClicked: {
                        root.selectCat=false
                        masterController.onPush_To_cart(model.id,model.name,model.category,model.quantity,model.cost,model.total,model.date,model.profit)
                        serch_text.text=''
                        selectmodel.model=''
                        reload()


                    }
                }

            }



        }

        Item{

            id:stock_id
            height: parent.height-rootcategory_id.height-50
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            TableView{
                id:salestable
                anchors.fill: parent

                TableViewColumn{

                    delegate: Rectangle{
                        height: 30
                        width:10
                        radius: 10
                        focus: true
                        Text {
                            anchors.centerIn: parent
                            text: "X"
                            font.bold: true
                            font.pixelSize: 12
                        }

                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                masterController.onRemoveRow(model.id)
                            }
                        }
                    }
                    width:40
                }
                TableViewColumn{
                    role:'name'
                    title: "NAME"
                    width: salestable.width/topid.col

                }

                TableViewColumn{
                    role:'cost'
                    title: "COST/ITEM"
                    width: salestable.width/topid.col
                }

                TableViewColumn{
                    id:qntcol
                    role:'quantity'
                    title: "QUANTITY"
                    width: salestable.width/topid.col
                    delegate:TextInput{
                        id:txtr
                        text:model.quantity
                        anchors.centerIn: parent
                        onTextChanged: {
                            if(model.quantity<1 && txtr.text<1){
                                txtr.text=""
                            }
                            else{
                                masterController.onQuantityChanged(model.id,Number(txtr.text))
                                txtr.text=model.quantity
                                reload()
                            }

                        }

                    }
                }




                TableViewColumn{
                    id:discounts
                    role:'discount'
                    title: "DISCOUNT"
                    width: salestable.width/topid.col
                    delegate:TextInput{
                        id:txtdiscount
                        text:model.discount
                        anchors.centerIn: parent

                        onTextChanged: {
                            if(model.quantity<1 && txtdiscount.text<1){
                                txtdiscount.text=""
                            }
                            else{
                                masterController.onDiscountChanged(model.id,Number(txtdiscount.text))
                                reload()

                            }
                        }

                    }

                }
                TableViewColumn{
                    id:tt_table
                    role:'total'
                    title: "TOTAL Amount"
                    width:salestable.width/topid.col
                }
                model:masterController.ui_Cart
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
        }
    }
    function reload(){
        salestable.__model=''
        salestable.__model=masterController.ui_Cart
        topid.totalcost=masterController.ui_Cart.ui_Grandtotal
        topid.amount= masterController.ui_Cart.ui_Amount
        topid.chnge=masterController.ui_Cart.ui_Grandtotal
        topid.tended=masterController.ui_Cart.ui_Tendered
        topid.discount=masterController.ui_Cart.ui_Discount
        topid.enable=true
    }


    Frame{
        id:salep_id
        anchors.top: parent.top;
        anchors.right: parent.right
        anchors.topMargin:parent.height/8.5
        anchors.rightMargin:parent.width/40
        height: parent.height/1.5
        width: parent.width/4-10
        background:Rectangle {
            color: masterController.ui_salestheme
        }

        Item{
            anchors.fill: parent
            id:payment_root
            Column{
                id:customername
                spacing: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                Label{
                    width: parent.width
                    text: "Enter Customer Name"
                    font.bold: true
                }
                TextField{
                    id:customernametxt
                    width: parent.width
                    height: 30
                    placeholderText:"Customer Name"
                }

            }
            Column{
                id:customerPhone
                spacing:3
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: customername.bottom
                Label{
                    width: parent.width
                    text: "Enter Customer phone"
                    font.bold: true
                }
                TextField{
                    id:customerPhonetxt
                    width: parent.width
                    height: 30
                    placeholderText: "phone number"
                }

            }

            Text {
                id:totalCost_id
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: customerPhone.bottom
                anchors.topMargin: 30
                anchors.leftMargin:0
                font.bold:true
                font.pixelSize:18
                text: qsTr("Total Cost:  "+topid.totalcost+'.00' )
            }
            Text {
                id:amount_id
                anchors.top: totalCost_id.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin:30
                anchors.leftMargin:0

                font.bold:true
                font.pixelSize:18
                text: qsTr(" Amout:  "+ topid.amount)
            }


            ComboBox {
                id:cmbpaymentype_id
                anchors.top: amount_id.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 30
                width: 200
                model: [ "Cash", "Mpesa"]
            }



            Rectangle{
                id:tenderd
                anchors.top: cmbpaymentype_id.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 30
                anchors.margins: 30
                height:40+tenderd_id.height

                Column{
                    spacing:10
                    Label{
                        text:"Amount Tendered "
                        anchors.bottomMargin: 30
                    }

                    TextInput{
                        id:tenderd_id
                        focus: true
                        text: topid.tended
                        width: parent.width
                        font.bold: true
                        // cursorVisible: true
                        onTextChanged: {
                            topid.tended=tenderd_id.text
                            topid.change=topid.tended-topid.totalcost
                        }
                    }
                }

            }
            Label{
                id:change_id
                anchors.top: tenderd.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.topMargin: 30
                anchors.margins: 30
                text: "Change :ksh "+topid.change+'.00'
                font.pixelSize: 20

            }
            Item{
                id:printing_id
                anchors.top: change_id.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 50
                Row{
                    spacing: 10
                    CheckBox{
                        id:print_id
                        onCheckedChanged: {

                        }
                    }
                    Label{
                        text: "print the receit"
                    }
                }
            }

            Item{
                id:suspend_cancel_id
                anchors.topMargin:30
                anchors.margins: 30
                anchors.top: printing_id.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                Row{
                    spacing: parent.width/2-80
                    Button{
                        text: "Cancel"
                        style: ButtonStyle {
                            background: Rectangle {
                                implicitWidth:80
                                implicitHeight: 30
                                border.width: control.activeFocus ? 2 : 1
                                border.color: "#888"
                                radius: 4
                                gradient: Gradient {
                                    GradientStop { position: 0 ; color: control.pressed ? "#eee" :"red"  }
                                    GradientStop { position: 1 ; color: control.pressed ?  "#ccc":"red" }
                                }
                            }
                        }
                        onClicked: {
                            topid.change=0
                            topid.totalcost=0
                            topid.amount=0
                            topid.tended=0
                            customernametxt.text=''
                            topid.enable=false
                            masterController.onClearcart()


                        }
                    }

                    Button{
                        text: "Payment"
                        enabled:topid.enable
                        style: ButtonStyle {
                            background: Rectangle {
                                implicitWidth:80
                                implicitHeight: 30
                                border.width: control.activeFocus ? 2 : 1
                                border.color: "gray"
                                radius: 4
                                gradient: Gradient {
                                    GradientStop { position: 0 ; color: control.pressed ?  "#eee": "green" }
                                    GradientStop { position: 1 ; color: control.pressed ?  "#ccc":  "green"}
                                }
                            }
                        }
                        onClicked: {

                            if(print_id.checkedState!==2){
                                receit_dialog_id.open()
                            }
                            else{
                                var res=_Recite_id.grabToImage(result=>{
                                                                   const resp= PrinteControl.printfun(result.image);
                                                                   result.saveToFile("C:/Users/Public/Pictures/img.png");
                                                                   if(resp){
                                                                       topid.change=0
                                                                       topid.totalcost=0
                                                                       topid.amount=0
                                                                       topid.tended=0
                                                                       customernametxt.text=''
                                                                       topid.enable=false
                                                                       masterController.onClearcart()
                                                                   }

                                                               })

                            }

                            //QString Recipttype, QString Grandtotal, QString Paymenttype, QString Change
                            masterController.onPayment(type_receit_id.currentIndex,Number(topid.totalcost),cmbpaymentype_id.currentText,Number(topid.change),Number(topid.discount))
                            type_receit_id.currentIndex=0


                        }

                    }
                    function lock(){

                        return false
                    }
                }

                //                Button{
                //                    anchors{
                //                        top: suspend_cancel_id.bottom
                //                        topMargin:50
                //                    }

                //                    text: "PayMent"
                //                    style: ButtonStyle {
                //                        background: Rectangle {
                //                            implicitWidth:200
                //                            implicitHeight: 30
                //                            border.width: control.activeFocus ? 3 : 2
                //                            border.color: "#888"

                //                            radius: 4
                //                            gradient: Gradient {
                //                                GradientStop { position: 0 ; color: control.pressed ? "#eee" :"red"  }
                //                                GradientStop { position: 1 ; color: control.pressed ?  "#ccc":"red" }
                //                            }
                //                        }
                //                    }
                //                    onClicked: {
                //                        submit_to_print()
                //                        if(print_id.checkedState!==2){
                //                            receit_dialog_id.open()
                //                        }
                //                        var res=_Recite_id.grabToImage(result=>{
                //                                                           result.saveToFile("C:/Users/Public/Pictures/img.png");
                //                                                       })

                //                    }
                //                }


            }


        }

    }
    Dialog{
        id:additem_dialog_id
        modality:Qt.WindowModal
        contentItem:Rectangle{
            implicitHeight: root.height/1.5
            implicitWidth: root.width/3
            Column{
                anchors.fill: parent
                Rectangle{
                    anchors.fill: parent
                    Column{
                        spacing: 10
                        anchors.fill: parent

                        Column{
                            spacing: 5
                            width: parent.width-50
                            anchors.horizontalCenter: parent.horizontalCenter
                            Label{
                                text:"DESCRIPTION"
                            }
                            TextField{
                                id:description
                                anchors.left: parent.left
                                anchors.right: parent.right
                                text: ""
                            }
                        }
                        Column{
                            spacing: 5
                            width: parent.width-50
                            anchors.horizontalCenter: parent.horizontalCenter
                            Label{
                                text:"AMOUNT"
                            }
                            TextField{
                                id:amount
                                anchors.left: parent.left
                                anchors.right: parent.right
                                text: ""
                            }
                        }
                    }

                }
                Row{
                    anchors.centerIn: parent
                    spacing:10
                    Button{
                        id:newitem_id

                        Text{
                            anchors.centerIn: parent
                            color: 'white'
                            text: "DISCARD"
                            font.bold: true
                        }

                        style: ButtonStyle {

                            background: Rectangle {
                                implicitWidth: 100
                                implicitHeight: 30
                                border.width: control.activeFocus ? 2 : 1
                                border.color: "#17a2b8"
                                radius: 4
                                gradient: Gradient {
                                    GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                                    GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                                }
                            }
                        }
                    }
                    Button{
                        id:submit_id

                        Text{
                            anchors.centerIn: parent
                            color: 'white'
                            text:  "SUBMIT"
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
                            additem_dialog_id.close()
                            // name, const QString category, const int quantity, const int price
                            masterController.onPushExpense(description.text,amount.text)
                            description.text=""
                            amount.text=""
                            masterController.onReload()

                        }
                    }
                }
            }
        }

    }
    Dialog{
        id:receit_dialog_id
        modality:Qt.WindowModal
        contentItem: Rectangle{
            implicitHeight: root.height/1.5
            implicitWidth: root.width/2

            PrintSale{
                id:print_Recite_id
                anchors{
                    left: parent.left
                    right: parent.right
                    top: print_btn.bottom
                }
                height:parent.height-parent.height/4
                change:topid.change
                totalcost:topid.totalcost
                rendard_amount: tenderd_id.text
                customer_name:customernametxt.text
                phone_number:customerPhonetxt.text
                transtype:saletype.text
            }
            Button{
                id:print_btn
                text: "PRINT"
                anchors{
                    top: parent.top
                    right: parent.right
                    rightMargin: 10
                }
                onClicked: {
                    var res=_Recite_id.grabToImage(result=>{
                                                       const resp= PrinteControl.printfun(result.image);
                                                       result.saveToFile("C:/Users/Public/Pictures/img.png");
                                                       if(resp){
                                                           topid.change=0
                                                           topid.totalcost=0
                                                           topid.amount=0
                                                           topid.tended=0
                                                           customernametxt.text=''
                                                           topid.enable=false
                                                           masterController.onClearcart()
                                                       }

                                                   })


                    receit_dialog_id.close()
                    topid.change=0
                    topid.totalcost=0
                    topid.amount=0
                    topid.tended=0
                    customernametxt.text=''
                    topid.enable=false
                    masterController.onClearcart()
                }
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth:80
                        implicitHeight:20
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#888"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ?  "#eee": "green" }
                            GradientStop { position: 1 ; color: control.pressed ?  "#ccc":  "green"}
                        }
                    }
                }

            }
        }

    }
    Rectangle{
        visible: false
        width:400
        height:500
        PrintSale{
            id:_Recite_id
            visible: false
            change:topid.change
            totalcost:topid.totalcost
            rendard_amount: tenderd_id.text
            customer_name:customernametxt.text
            phone_number:customerPhonetxt.text
            //         topid.amount=0

        }
    }
    Dialog{
        id:suspendeditem_dialog_id
        title: "Suspended Items"
        modality:Qt.WindowModal
        contentItem: Rectangle{
            implicitHeight: model_view_id.count*100
            implicitWidth: root.width/1.5
            Rectangle{
                id:header_id
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.top

                }
                height: 30
                width: parent.width
                color: 'black'
                Row{
                    spacing: 10
                    Frame{
                        height: 30
                        width: header_id.width/5
                        Text {
                            anchors.centerIn: parent
                            color: "white"
                            font.bold: true
                            font.pixelSize: 14
                            text: qsTr("Document")
                        }
                    }
                    Frame{
                        height: 30
                        width: header_id.width/5
                        Text {
                            anchors.centerIn: parent
                            color: "white"
                            font.bold: true
                            font.pixelSize: 14
                            text: qsTr("Date")
                        }
                    }
                    Frame{
                        height: 30
                        width: header_id.width/5
                        Text {
                            anchors.centerIn: parent
                            color: "white"
                            font.bold: true
                            font.pixelSize: 14
                            text: qsTr("Customer")
                        }
                    }
                    Frame{
                        height: 30
                        width: header_id.width/5
                        Text {
                            anchors.centerIn: parent
                            color: "white"
                            font.bold: true
                            font.pixelSize: 14
                            text: qsTr("Employee")
                        }
                    }
                    Frame{
                        height: 30
                        width: header_id.width/5
                        Text {
                            anchors.centerIn: parent
                            color: "white"
                            font.bold: true
                            font.pixelSize: 14
                            text: qsTr("Action")
                        }
                    }


                }

            }

            ListView{
                id:model_view_id
                spacing: 5
                anchors{
                    left: parent.left
                    right: parent.right
                    top: header_id.bottom
                }
                height: model_view_id.count*50
                model: [1,2,3]
                delegate: Rectangle{
                    width: parent.width
                    color: "gray"
                    height: 50
                    Row{
                        spacing: 10
                        Rectangle{
                            height: 30
                            color: "gray"
                            width: header_id.width/5
                            Text {
                                anchors.centerIn: parent
                                color: "white"
                                font.bold: true
                                font.pixelSize: 14
                                text: qsTr("Document"+model.index)
                            }
                        }
                        Rectangle{
                            height: 30
                            width: header_id.width/5
                            color: "gray"
                            Text {
                                anchors.centerIn: parent
                                color: "white"
                                font.bold: true
                                font.pixelSize: 14
                                text: qsTr("Date")
                            }
                        }
                        Rectangle{
                            height: 30
                            width: header_id.width/5
                            color: "gray"
                            Text {
                                anchors.centerIn: parent
                                color: "white"
                                font.bold: true
                                font.pixelSize: 14
                                text: qsTr("Customer")
                            }
                        }
                        Rectangle{
                            height: 30
                            width: header_id.width/5
                            color: "gray"
                            Text {
                                anchors.centerIn: parent
                                color: "white"
                                font.bold: true
                                font.pixelSize: 14
                                text: qsTr("Employee"+model.index)
                            }
                        }
                        Rectangle{
                            height: 30
                            width: header_id.width/5
                            color: "gray"
                            Button{
                                anchors.centerIn: parent
                                text: " Unsuspend"
                            }
                        }

                    }
                }
            }

            Button{
                id:closebtn
                anchors{
                    top: model_view_id.bottom
                    right: parent.right
                    topMargin: 60
                    rightMargin: 20
                }
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth:60
                        implicitHeight:30
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#7b8a8b"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#7b8a8b": "rgba(0, 0, 0, 0.15)" }
                            GradientStop { position: 1 ; color: control.pressed ?  "#7b8a8b":  "rgba(0, 0, 0, 0.15)"}
                        }
                    }
                    label:Label {
                        anchors.centerIn: parent
                        color: "white"
                        font.bold: true
                        text: " Close"

                    }
                }

                onClicked:{
                    suspendeditem_dialog_id.close()
                }

            }


        }

    }
    Rectangle{
        visible: false
        y:0
        width:2000
        height:1380
        PrintSales{
            id:printSales
        }

    }
    Dialog{
        id:viewstock
        modality:Qt.WindowModal
        height: parent.height-parent.height/8
        width: parent.width-parent.width/6
        contentItem: Rectangle{
            anchors.fill: parent

            Rectangle{
                id:search
                border.color:'gray'
                radius: 4
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.rightMargin: 10
                 anchors.bottomMargin: 20
                width: 200
                height: 30
                focus: true
                TextInput{
                    id:search_text
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right

                    text: ""
                    focus: true
                    font.bold: true
                    cursorVisible: true

                    onTextChanged: {
                        masterController.onStock_search(search_text.text)
                        returnstable.model=masterController.ui_Stocks
                    }


                }

            }
            TableView{
                id:returnstable
                anchors{
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                    top: search.bottom
                    topMargin: 20
                }

                TableViewColumn{
                    role:'id'
                    title: "ReciteNo"
                    width: returnstable.width/5
                }
                TableViewColumn{
                    role:'name'
                    title: "item Name"
                    width: returnstable.width/5
                }
                TableViewColumn{
                    role:'amount'
                    title: "Amount if items"
                    width: returnstable.width/5
                }
                TableViewColumn{
                    role:'maxdiscount'
                    title: "maximum Discount"
                    width: returnstable.width/5
                }

                TableViewColumn{
                    role:'price'
                    title: "Cost per Item"
                    width: returnstable.width/5
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
        id:dailyreport
        modality:Qt.WindowModal
        height: parent.height-parent.height/8
        width: parent.width-parent.width/6
        contentItem: Rectangle{
            anchors.fill: parent
            Button{
                id:printdailyreport
                anchors{
                    top: parent.top
                    right: parent.right
                    topMargin: 5
                }
                text: "Print"
                onClicked: {
                    let datasale=printSales.grabToImage(result=>{
                                                            PrinteControl.printfun(result.image);
                                                            result.saveToFile("C:/Users/Public/Pictures/salesCashier.png");
                                                        } )
                }
                style: ButtonStyle {
                    background: Rectangle {
                        implicitWidth: 100
                        implicitHeight: 30
                        border.width: control.activeFocus ? 2 : 1
                        border.color: "#17a2b8"
                        radius: 4
                        gradient: Gradient {
                            GradientStop { position: 0 ; color: control.pressed ? "#138496" : "#17a2b8" }
                            GradientStop { position: 1 ; color: control.pressed ? "#138496" : "#17a2b8" }
                        }
                    }
                }
            }
            PrintSales{
                anchors{
                    top: printdailyreport.bottom
                    left: parent.left
                    bottom: parent.bottom
                    right: parent.right
                }
            }
        }
    }

}
