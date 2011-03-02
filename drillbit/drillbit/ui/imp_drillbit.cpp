#include "imp_drillbit.h"

DrillbitWin::DrillbitWin(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

}


void DrillbitWin::on_mnuFileExit_triggered(bool checked)
{
    exit(0);
}
