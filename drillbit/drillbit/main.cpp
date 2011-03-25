#include <QApplication>
#include "ui/imp_drillbit.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    //configure application for QSettings
    QCoreApplication::setOrganizationName("otaku-elite");
    QCoreApplication::setOrganizationDomain("otaku-elite.com");
    QCoreApplication::setApplicationName("Lyngo Driller");

    DrillbitWin dwin;
    dwin.show();

    return app.exec();
}
