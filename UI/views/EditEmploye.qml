import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Item {
    anchors.fill: parent;
    property alias lname: lnametxt.text
    property alias  fname: fnametxt.text
    property alias  email: emailtxt.text
    property alias username: usernametxt.text
    property alias password: passnametxt.text
    property alias  gender: gender.currentIndex
    property alias role: role.currentIndex
    property alias phone: phonetxt.text
    property alias idroot: labelid.text
  Rectangle{
      id:fnameroot
       height: fnametxt.height*2
      color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: parent.top
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "First Name"
          }
          TextField{
              id:fnametxt
              anchors.left: parent.left
              anchors.right: parent.right
              text: ""
          }
      }
  }
  Rectangle{
      id:lnameroot
       height: fnametxt.height*2
          color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: fnameroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "last Name"
          }
          TextField{
              id:lnametxt
              anchors.left: parent.left
              anchors.right: parent.right
              text: ""
          }
      }
  }
  Rectangle{
      id:usernameroot
       height: fnametxt.height*2
          color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: lnameroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "UserName"
          }
          TextField{
              id:usernametxt
              anchors.left: parent.left
              anchors.right: parent.right
              text: ""
          }
      }
  }
  Rectangle{
      id:passnameroot
      height: fnametxt.height*2
         color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: usernameroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "Password"
          }
          TextField{
              id:passnametxt
              anchors.left: parent.left
              anchors.right: parent.right
              text: ""
          }
      }
  }
  Rectangle{
      id:emailroot
         color: "transparent"
      height: fnametxt.height*2
      anchors{
          left: parent.left
          right: parent.right
          top: passnameroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "Email"
          }
          TextField{
              id:emailtxt
              anchors.left: parent.left
              anchors.right: parent.right
              text: ""
          }
      }
  }
  Rectangle{
      id:genderroot
      height: fnametxt.height*2
         color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: emailroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: " Gender"
          }
          ComboBox{
              id:gender
              anchors{
                  left: parent.left
                  right: parent.right
              }
              model: ["Male","Female"]
          }
      }
  }
  Rectangle{
      id:roleroot
      height: fnametxt.height*2
         color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: genderroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "User Role"
          }
          ComboBox{
              id:role
              anchors{
                  left: parent.left
                  right: parent.right
              }

              model: ["Manager","Cashier"]
          }
      }
  }
  Rectangle{
      id:phoneroot
       height: fnametxt.height*2
         color: "transparent"
      anchors{
          left: parent.left
          right: parent.right
          top: roleroot.bottom
          topMargin: 10
      }

      Column{
          spacing: 5
          anchors.fill: parent
          Label{
              text: "Phone Number"
          }
          TextField{
              id:phonetxt
              anchors.left: parent.left
              anchors.right: parent.right
              placeholderText: "Phone..."
              text: ""
          }
      }
  }
  Label{
      id:labelid
      visible: false
      text:''
  }

  Rectangle{
      height: 50
      width: parent.width
      anchors.top: phoneroot.bottom
      anchors.topMargin: 10
      Row{
          spacing: parent.width/10
          anchors.centerIn: parent
         Button{
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

                 clear()
                   editemployeAdd.close()
             }
         }
         Button{
             text: "Submit"
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
                 console.log(labelid.text)
                 masterController.onUpdate_employee(labelid.text,fnametxt.text, gender.currentText,  lnametxt.text, role.currentIndex,emailtxt.text,usernametxt.text,passnametxt.text,phonetxt.text)
                 masterController.onReload()
                 clear()
                   editemployeAdd.close()
             }
         }
      }
  }
  function clear(){
      fnametxt.text=""
      gender.currentIndex=0
      lnametxt.text=""
      role.currentIndex=0
      emailtxt.text=""
      usernametxt.text=""
      passnametxt.text=""
  }
}
