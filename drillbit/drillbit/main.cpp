#include <QApplication>
#include "ui/imp_drillbit.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    DrillbitWin dwin;
    dwin.show();

    return app.exec();
}
