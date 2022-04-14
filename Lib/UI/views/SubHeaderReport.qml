import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    id:headerroot
    property alias root_id: headerroot.myid
    property string myid
    property bool searchtxtvisible:filtercmb.visible

    Frame{
        id:fram_id
        anchors.fill: parent
        background: Rectangle{
            border.color: 'transparent'
        }

        Rectangle{
            id:serch_id

            border.color:'green'
            radius: 4
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.rightMargin: 10
            width:200
            height: parent.height

            focus: true
            TextInput{
                id:serch_text
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 5
                text: ""
                focus: true
                cursorVisible: true
                onTextChanged: {
                    masterController.onSearch(headerroot.myid,serch_text.text,filtercmb.currentIndex)
                }
            }
        }
        Rectangle{
            id:days_id
           visible:searchtxtvisible
            anchors{
                left: serch_id.right
                leftMargin: 10
            }
            border.color:'black'
            radius: 4
            width:200
            height: parent.height

         ComboBox{
             id:filtercmb
             anchors.fill: parent
             model:["Todays","Yesterday","Last 7 Days","Last 30 Days","Current Month","Current Year","Last Year","All Time"]
             onCurrentIndexChanged: {
                  masterController.onSearch(headerroot.myid,serch_text.text,filtercmb.currentIndex)
             }
         }

        }
        Button{
            id:print_report_id
            text:"Print"
            anchors{
                right: parent.right
                rightMargin: 20
            }
            implicitWidth: 90
            implicitHeight: 30
            style: ButtonStyle{
                background:Rectangle{
                    color:"skyblue"
                    radius: 5
                }
            }
            onClicked:{
                const cur=print_report_id.currentText
                print_report_id.currentIndex=0
                console.log("Selected one=> "+cur)
            }
        }
        Button{
            id:export_id
            text: "Export"
            anchors{
                right: print_report_id.left
                rightMargin: 20
            }
            implicitWidth: 90
            implicitHeight: 30
            style: ButtonStyle{
                background:Rectangle{
                    color:"skyblue"
                    radius: 5
                }
            }
            onClicked: {
                masterController.onExport_to_csvQuery(headerroot.myid,filtercmb.currentIndex,serch_text.text)


            }
        }
    }
    Dialog{
        id:selectcalender
        height:300
        width: 200
        Calendar{
            id:cal
           locale: Qt.locale("en_AU")
            anchors.fill: parent
            minimumDate: new Date(2017, 0, 1)
            maximumDate: new Date(new Date().getFullYear(),new Date().getMonth()-1, new Date().getDate())
            onClicked: {
               selectcalender.close()
               days_idtxt.text= masterController.onFomatDate(date)
            }

        }
    }

}
