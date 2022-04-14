#include <QApplication>
#include <QQmlApplicationEngine>
#include<QtQuickControls2>
#include<QQmlContext>
#include<Controller/mastercontroller.h>
#include<Controller/navigation-controller.h>
#include<QIcon>
#include<Printer/printecontrol.h>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    //SETTINGS


     Controller::MasterController MasterController;
    QFont serifFont(MasterController.getFonttype(), MasterController.getMfontSize());
    //QFont serifFont("Times", 10);
    app.setFont(serifFont);
    app.setWindowIcon(QIcon("preload"));
    app.setOrganizationName("brighttech");
    app.setOrganizationDomain("nzuritech");

    //qmlRegisterType<Controller::MasterController>("Lib",1,0,"Mastercontroller");
     qmlRegisterType<Controller::NavigationController>("Lib", 1, 0,"NavigationController");
     Printer::PrinteControl printers;
     QQmlApplicationEngine engine;
     engine.rootContext()->setContextProperty("masterController",&MasterController);
     engine.rootContext()->setContextProperty("PrinteControl",&printers);

    const QUrl url(QStringLiteral("qrc:/views/main.qml"));
    engine.load(url);

    return app.exec();
}
