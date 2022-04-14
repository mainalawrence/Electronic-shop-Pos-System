import QtQuick 2.0
import Qt.labs.platform 1.1

Item {

    FileDialog {

        id: fileDialog
        title: "Please choose a file"
        nameFilters: ["Text files (*.csv)", "Text files(*.xlsx)"]
        currentFile: document.source
             folder: StandardPaths.writableLocation(StandardPaths.DocumentsLocation)
        onAccepted: {
            masterController.onImport("stock",fileUrl)
        }
        onRejected: {
            console.log("Canceled")

        }

    }
}
