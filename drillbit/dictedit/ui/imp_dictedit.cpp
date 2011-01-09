#include "imp_dictedit.h"

DictEditWin::DictEditWin (QWidget *parent)
    :QMainWindow(parent)
{
    setupUi(this);

    connect(this->mnuExit, SIGNAL(triggered(bool)),
            QCoreApplication::instance(), SLOT(quit()));

}

void DictEditWin::on_mnuOpen_triggered(bool)
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open file..."),
            QString(),
            tr("Lyngo Drillbit (*.ldb)")
    );

    this->_dictionary.load(fileName);

    // propagate data into widgets
    update_widgets();

}

/**
 * @brief
 *  Update widgets with proper values.
 */
void DictEditWin::update_widgets(void)
{
    // load the tree widget.
    this->twWordBank->clear();
    this->leUnitTitle->setText("[Unit Title]");

    if (!this->_dictionary.name().isEmpty())
        this->leUnitTitle->setText(this->_dictionary.name());

    for (int i = 0; i < this->_dictionary.count(); ++i) {
        QTreeWidgetItem *item = new QTreeWidgetItem(this->_dictionary.itemAt(i));
        DEBUG_PRINT(this->_dictionary.itemAt(i).join(", ").toStdString().c_str());
        this->twWordBank->addTopLevelItem(item);
    }
}
