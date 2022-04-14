#include "printecontrol.h"
#include<QPrintDialog>
#include<QPrinter>
#include <QPixmap>
#include <QImage>
#include <QPrintEngine>
#include<QPainter>
#include<QPdfWriter>
#include <QDebug>
using namespace Printer;

PrinteControl::PrinteControl(QObject *parent) : QObject(parent)
{
name=false;
}

bool PrinteControl::printfun(QVariant data)
{
    QImage img = qvariant_cast<QImage>(data);
    img.save("C:/Users/Public/Pictures/picprint.png","PNG");
//    QPrinter printer2;
//    printer2.setOutputFormat(QPrinter::PdfFormat);
//    printer2.setOutputFileName("C:/Users/Public/Pictures/nonwritable.pdf");
//    QPainter painter;
//         if (! painter.begin(&printer2)) { // failed to open file
//             qWarning("failed to open file, is it writable?");
//             return 1;
//         }
//         painter.drawImage(QPoint(0,0),img);
//         if (! printer2.newPage()) {
//             qWarning("failed in flushing page to disk, disk full?");
//             return 1;
//         }
//         painter.drawText(10, 10, "Test 2");
//         painter.end();

    QPrinter printer;
    QPrintDialog *dlg = new QPrintDialog(&printer,0);
    if(dlg->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        painter.drawImage(QPoint(0,0),img);
        painter.end();
        name=true;
    }

    return true;
}

bool PrinteControl::getName() const
{
    return name;
}
