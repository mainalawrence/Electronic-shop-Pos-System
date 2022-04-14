import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Qt.labs.platform 1.1
import QtQuick.Dialogs 1.2


Item {
    id:root
    property string com_logo:"C:\Users\Admin\Downloads\test.png"
    property int id
    property int role
    property string lname
    property string fname
    property string email
    property string username
    property string password
    property string gender
    property string phone

    //themes
       property string backgroundthemecolor
       property string loginthemecolor
       property string salesthemecolor
    property string  fonttype
    Button{
        x:5
        y:5
        text: "Home"
        onClicked: {
            masterController.ui_navigation.goCreatedashboardView()
        }
    }
    Item{
        id: name
        anchors.fill: parent
        TabView {
            id: frame
            anchors.fill: parent
            anchors.margins: 4
            anchors.topMargin: 30
            Tab { title: "Employee"
                Item
                {
                    anchors.fill: parent
                    Frame
                    {
                        id:header_id
                        height: 50
                        anchors{
                            left: parent.left
                            right:parent.right
                            top: parent.top
                        }
                        background: Rectangle{color:"Transparent"}
                        Button{
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: parent.width/20
                            text: "New Employee"
                            style: ButtonStyle {
                                background: Rectangle {
                                    implicitWidth: 150
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
                                employeAdd.open()
                            }
                        }
                    }
                    Frame
                    {
                        id:middle_search_id
                        height: 50
                        anchors{
                            left: parent.left
                            right:parent.right
                            top: header_id.bottom
                        }
                        background: Rectangle{color:"gray"}
                        Rectangle{
                            id:serch_id
                            color: "white"
                            anchors.right: export_btn.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: parent.width/60
                            width: 250
                            height: 30
                            radius: 5
                            TextInput{
                                id:serch_text
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.left: parent.left
                                anchors.right: parent.right
                                text: ""
                                font.bold: true
                                cursorVisible: true
                                onTextChanged: {
                                    masterController.onEmployee_search(serch_text.text)
                                    employyetable.model=masterController.ui_employee

                                }


                            }

                        }
                        Button{
                            id:export_btn
                            text: "Export"
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.rightMargin: parent.width/60
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
                                masterController.onExport_to_csv("employee","")
                            }
                        }
                    }
                    Rectangle{
                        id:body_id
                        property int col: 10
                        anchors{
                            left: parent.left
                            right:parent.right
                            top: middle_search_id.bottom
                            bottom: parent.bottom
                            bottomMargin: parent.height/20
                        }
                        color: "Transparent"

                        TableView{
                            id:employyetable
                            anchors.fill: parent
                            model:masterController.ui_employee
                            TableViewColumn{
                                role:'id'
                                title: "Id"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'fname'
                                title: "First Name"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'lname'
                                title: "Last Name"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'phone'
                                title: "phone"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'username'
                                title: "Username"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'password'
                                title: "password"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'email'
                                title: "email"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'gender'
                                title: "Gender"
                                width:body_id.width/body_id.col
                            }
                            TableViewColumn{
                                role:'role'
                                title: "role"
                                width:body_id.width/body_id.col
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
                                                masterController.onRemoveEmployerr(model.id)
                                                masterController.onReload()
                                            }
                                        }
                                        Button{
                                            text: "Edit"
                                            height: 5*3
                                            onClicked: {
                                                root.lname=model.lname
                                                root.fname=model.fname
                                                root.email=model.email
                                                root.username=model.username
                                                root.password=model.password
                                                root.gender=model.gender
                                                root.role=model.role
                                                root.phone=model.phone
                                                root.id=model.id
                                                editemployeAdd.open()
                                            }

                                        }
                                    }
                                }
                            }

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

            }

            //the information part
            Tab {
                title: "Information "
                Item
                {
                    anchors.fill: parent
                    Frame{
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.margins: parent.width/60
                        anchors.bottomMargin: parent.height/4
                        width: parent.width/3
                        Label{
                            id:comp_name_id
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.topMargin: parent.height/20
                            height: 20
                            text: "Company Name:"

                        }
                        TextField{
                            id:txtcompany_name
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: comp_name_id.bottom
                            height: 30
                            text:masterController.ui_companyName

                        }
                        //company logo



                        //address

                        Label{
                            id:comp_address_id
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.topMargin: parent.height/20
                            anchors.top: txtcompany_name.bottom
                            height: 20
                            text: "Company Address:"

                        }
                        TextField{
                            id:txtaddress
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: comp_address_id.bottom
                            height: 30
                            text: masterController.ui_companyaAddress

                        }
                        //number


                        Label{
                            id:comp_number_id
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.topMargin: parent.height/20
                            anchors.top: txtaddress.bottom
                            height: 20
                            text: "Company Number:"

                        }
                        TextField{
                            id:txtnumber
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: comp_number_id.bottom
                            height: 30
                            text: masterController.ui_companyNumber

                        }

                        //  email
                        Label{
                            id:comp_email_id
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: txtnumber.bottom
                            anchors.topMargin: parent.height/20
                            height: 20
                            text: "Company Email:"

                        }
                        TextField{
                            id:txtemail
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: comp_email_id.bottom
                            height: 30
                            text: masterController.ui_companyEmail

                        }


                        //policy
                        Label{
                            id:comp_policy_id
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: txtemail.bottom
                            anchors.topMargin: parent.height/20
                            height: 20
                            text: "Return Policy:"

                        }
                        TextField{
                            id:txtpolicy
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: comp_policy_id.bottom
                            height: 30
                            text: masterController.ui_companyapolicies

                        }
                        Row{
                            id:btn_info_id
                            anchors.topMargin: parent.height/10
                            anchors.top: txtpolicy.bottom
                            anchors.margins: parent.width/20
                            anchors.horizontalCenter: parent.horizontalCenter
                            height: 30
                            spacing: parent.width/1.5-(discard_id.width*2)
                            Button{
                                id:discard_id
                                text: "Discard"
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
                                    masterController.ui_navigation.goCreatedashboardView()
                                }
                            }
                            Button{
                                text: "Save"
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
                                    masterController.onSaveCompanyinfor(txtcompany_name.text,txtaddress.text,txtnumber.text,txtemail.text,txtpolicy.text)
                                }

                            }

                        }



                    }

                }

            }
            //color of the sysyem
            /*

                home page color
                home page image

                default color

              */
            Tab { title: "Themes"
                Item
                {
                    anchors.fill: parent
                    Frame
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        anchors.margins: parent.width/60
                        anchors.bottomMargin: parent.height/3
                        width: parent.width/4

                        Rectangle{
                            id:fontsize
                            height: 60
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: parent.top
                            }

                            Label{
                                id:titlefont
                                text: "Set the fontsize"
                                font.underline: true
                                font.italic: true
                                font.bold:true
                                anchors{
                                    top: parent.top
                                    left: parent.left
                                    right: parent.right
                                }
                                height: 25
                            }

                            Row{
                                spacing: 10
                                anchors{
                                    top: titlefont.bottom
                                    left: parent.left
                                    right: parent.right
                                }
                                Button{
                                    text: "Font"
                                    onClicked: {
                                        fontDialog.open();
                                        root.fonttype=fontDialog.font
                                    }
                                }

                                Rectangle{

                                    height: themecolor.height
                                    width: parent.width-themecolor.width
                                    Text{
                                        id:fonttxt
                                        anchors.fill: parent
                                        text: fontDialog.font
                                    }
                                }
                            }
                        }
                        Rectangle{
                            id:logincolor
                            anchors{
                                left: parent.left
                                right: parent.right
                                top: fontsize.bottom
                            }
                            height: 70
                            Label{
                                id:titlelogincolor
                                text: "Set the Login Theme Color"
                                font.underline: true
                                font.italic: true
                                font.bold:true
                                anchors{
                                    top: parent.top
                                    left: parent.left
                                    right: parent.right
                                }
                                height: 25
                            }

                            Row{
                                spacing: 10
                                anchors{
                                    top: titlelogincolor.bottom
                                    left: parent.left
                                    right: parent.right
                                }

                                Button{
                                    id:themecolor
                                    text: "Theme"
                                    onClicked: {
                                       loginthemecolorid.open();
                                        root.loginthemecolor=loginthemecolorid.color
                                    }
                                }

                                Rectangle{
                                    height: themecolor.height
                                    width: parent.width-themecolor.width
                                    color:root.loginthemecolor
                                }
                            }
                        }

                        Rectangle{
                            id:backgroundcolor

                            anchors{
                                left: parent.left
                                right: parent.right
                                top: logincolor.bottom
                            }
                            height: 70
                            Label{
                                id:titlebackgroundcolor
                                text: "Set the BackGround Theme Color"
                                font.underline: true
                                font.italic: true
                                font.bold:true
                                anchors{
                                    top: parent.top
                                    left: parent.left
                                    right: parent.right
                                }
                                height:25
                            }

                            Row{
                                spacing: 10
                                anchors{
                                    top: titlebackgroundcolor.bottom
                                    left: parent.left
                                    right: parent.right
                                }

                                Button{
                                    id:backgroundthemecolor
                                    text: "Theme"
                                    onClicked: {
                                        backgroundthemecolorid.open();
                                       root.backgroundthemecolor =backgroundthemecolorid.color
                                    }
                                }

                                Rectangle{
                                    height: themecolor.height
                                    width: parent.width-themecolor.width
                                    color:root.backgroundthemecolor
                                }
                            }
                        }

                        Rectangle{
                            id:salecolor

                            anchors{
                                left: parent.left
                                right: parent.right
                                top: backgroundcolor.bottom
                            }
                            height: 70
                            Label{
                                id:titlesalecolor
                                text: "Set the Sales Theme Color"
                                font.underline: true
                                font.italic: true
                                font.bold:true
                                anchors{
                                    top: parent.top
                                    left: parent.left
                                    right: parent.right
                                }
                                height:25
                            }

                            Row{
                                spacing: 10
                                anchors{
                                    top: titlesalecolor.bottom
                                    left: parent.left
                                    right: parent.right
                                }

                                Button{
                                    id:salethemecolor
                                    text: "Theme"
                                    onClicked: {
                                        salesthemecolorid.open();
                                       root.salesthemecolor=salesthemecolorid.color
                                    }
                                }
                                Rectangle{
                                    height: themecolor.height
                                    width: parent.width-themecolor.width
                                    color:root.salesthemecolor
                                }
                            }
                        }

                        Rectangle{
                            id:buttonsave
                            height: savebtn.height+40
                            anchors{
                                topMargin: parent.height/10
                                left: parent.left
                                right: parent.right
                                top: salecolor.bottom
                            }
                            Button{
                                id:savebtn
                                text: "Save Chenges"
                                anchors.horizontalCenter: parent.horizontalCenter
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
                                    console.log(root.fonttype+" "+root.loginthemecolor+" "+root.backgroundthemecolor+" "+root.salesthemecolor)
                                    masterController.onSavethemes(root.fonttype,root.loginthemecolor,root.backgroundthemecolor,root.salesthemecolor)
                                }

                            }
                        }

                    }
                }

            }
            /*
                export database
                backup

            Tab { title: "Database"
                visible: false
                Item
                {
                    anchors.fill: parent
                    Frame
                    {
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.top: parent.top
                        height: parent.height/4
                        anchors.margins: parent.width/60
                        width: parent.width/4
                        Column{
                            spacing: 50
                            Column{
                                spacing: 10
                                Row{
                                    Label{
                                        text: "DataBase Name :"

                                    }
                                    TextField{
                                        id:input
                                    }

                                }
                                Button{
                                    text:"Save"
                                }
                            }
                            Button{
                                text: "BackUP database"
                                onClicked: {
                                    masterController.onBackupd("")
                                }
                            }
                            Button{
                                text: "Restore database"
                                onClicked: {
                                    masterController.onBackupd("")
                                }
                            }
                        }


                    }
                }
            }*/

            style: TabViewStyle {
                frameOverlap: 1
                tabsAlignment : Qt.AlignHCenter
                tabsMovable:false
                tab: Rectangle {
                    color: "transparent"
                    border.color:  "transparent"
                    implicitWidth: Math.max(text.width + 4, 80)
                    implicitHeight: 30

                    radius: 4
                    Text {
                        id: text
                        font.pixelSize: 16
                        anchors.centerIn: parent
                        text: styleData.title
                        color: styleData.selected ? "skyblue" : "#20c997"
                    }
                }
                frame: Rectangle { }
            }

        }

    }
    Dialog{
        id:employeAdd
        modality:Qt.WindowModal
        contentItem: Rectangle{
            implicitHeight: root.height/1.5
            implicitWidth: root.width/3
            EmployeAdd{
                anchors.fill: parent
                anchors.leftMargin: parent.width/15
                anchors.rightMargin: parent.width/15

            }}
    }
    Dialog{
        id:editemployeAdd
        modality:Qt.WindowModal
        contentItem: Rectangle{
            implicitHeight: root.height/1.5
            implicitWidth: root.width/3
            EditEmploye{
                anchors.fill: parent
                anchors.leftMargin: parent.width/15
                anchors.rightMargin: parent.width/15
                lname:root.lname
                fname:root.fname
                email:root.email
                username:root.username
                password:root.password
                gender: root.gender
                role:root.role
                phone:root.phone
                idroot:root.id
            }}
    }
    FontDialog {
        id: fontDialog
        currentFont.family: document.font

    }
    ColorDialog{
        id:colorDialog
    }
    ColorDialog{
        id:loginthemecolorid

    }
    ColorDialog{
        id:backgroundthemecolorid

    }
    ColorDialog{
        id:salesthemecolorid
    }
}
