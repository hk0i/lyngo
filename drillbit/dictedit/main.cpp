#include <QApplication>
#include "ui/imp_dictedit.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    DictEditWin win;
    win.show();

    return app.exec();
}
