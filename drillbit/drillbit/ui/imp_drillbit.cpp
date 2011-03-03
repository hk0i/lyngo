#include "imp_drillbit.h"

DrillbitWin::DrillbitWin(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

}


void DrillbitWin::on_mnuFileExit_triggered(bool checked)
{
    QCoreApplication::quit();
}

void DrillbitWin::on_mnuFileOpenVocabulary_triggered(bool checked)
{
    // get file name
    QString filename;
    filename = QFileDialog::getOpenFileName(this,
            tr("Open drillbit dictionary..."),
            "",
            tr("Lyngo Drillbit Dictionaries (*.ldb)")
    );
    // load it into lyquiz
    if (!filename.isEmpty()) {
        LyDict tmpDict;
        tmpDict.load(filename);
        _quiz.loadDictionary(tmpDict);
    }
}
