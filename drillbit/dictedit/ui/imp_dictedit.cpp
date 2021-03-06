#include "imp_dictedit.h"

DictEditWin::DictEditWin (QWidget *parent)
    :QMainWindow(parent)
{
    setupUi(this);

    connect(this->mnuExit, SIGNAL(triggered(bool)),
            QCoreApplication::instance(), SLOT(quit()));

    this->_dictionary = new LyDict();
}

DictEditWin::~DictEditWin(void)
{
    if (this->_dictionary)
        delete this->_dictionary;
}

/**
 * @brief
 *  Menu open event
 */
void DictEditWin::on_mnuOpen_triggered(bool)
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("Open file..."),
            QString(),
            tr("Lyngo Drillbit (*.ldb)")
    );

    if (fileName.isEmpty())
        return;

    // Delete the previous dictionary, if one exists.
    if (this->_dictionary)
        delete this->_dictionary;
    this->_dictionary = new LyDict();
    this->_dictionary->load(fileName);
    this->_current_file = fileName;

    // propagate data into widgets
    update_widgets();

}

/**
 * @brief
 *  File > New clicked event; creates a new dictionary and deletes the old
 *  one
 */
void DictEditWin::on_mnuNew_triggered(bool)
{
    _current_file = "";

    if (_dictionary) {
        qDebug() << "file new: deleting old dictionary";
        delete this->_dictionary;
    }
    qDebug() << "file new: creating new dictionary";
    _dictionary = new LyDict();
    qDebug() << "file new: update widgets";
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

    if (!this->_current_file.isEmpty())
        this->update_window_title();
    if (!this->_dictionary->name().isEmpty())
        this->leUnitTitle->setText(this->_dictionary->name());

    // clear line edits and reset combo box
    leWord->clear();
    cmbPartOfSpeech->setCurrentIndex(0);
    leDefinition->clear();

    qDebug() << "update_widgets: populating list data...";

    for (int i = 0; i < this->_dictionary->count(); ++i) {
        QTreeWidgetItem *item = new QTreeWidgetItem(this->_dictionary->itemAt(i)->data(false));
        qDebug() << this->_dictionary->itemAt(i)->data().join(", ");
        this->twWordBank->addTopLevelItem(item);
    }

    // set focus to title box
    leUnitTitle->setFocus();
}

/**
 * @brief
 *  Saves the currently open file; if there is no file currently open
 *  on_mnuSaveAs_triggered() is called to establish one and save
 */
void DictEditWin::on_mnuSave_triggered(bool)
{
    if (!this->_current_file.isEmpty())
        this->_dictionary->save(this->_current_file);
    else
        on_mnuSaveAs_triggered(false);
}

void DictEditWin::on_mnuSaveAs_triggered(bool)
{
    QString fileName = QFileDialog::getSaveFileName(
            this,
            tr("Save dictionary..."),
            QString(),
            tr("Lyngo Drillbit (*.ldb)")
    );

    if (this->_dictionary) {
        this->_dictionary->save(fileName);
        this->_current_file = fileName;
    }
}

/**
 * @brief
 *  Updates the window title to display the application name and current file
 *  name that is being edited.
 */
void DictEditWin::update_window_title(void)
{
    QString title;
    title = "Lyngo Drillbit Editor";
    if (!this->_current_file.isEmpty())
        title += " - [" + this->_current_file + "]";
    this->setWindowTitle(title);
}

void DictEditWin::on_twWordBank_currentItemChanged(QTreeWidgetItem *newItem,
        QTreeWidgetItem *oldItem)
{
    if (newItem) {
        this->leWord->setText(newItem->text(0));
        this->cmbPartOfSpeech->setCurrentIndex(
                cmbPartOfSpeech->findText(newItem->text(1))
        );
        this->leDefinition->setText(newItem->text(2));
    }
}

/**
 * @brief
 *  Adds a word to the dictionary.
 */
void DictEditWin::on_pbAdd_clicked(void)
{
    if (!leWord->text().isEmpty() && !leDefinition->text().isEmpty()) {
        this->_dictionary->add(leWord->text(),
                this->_dictionary->posFromName(
                    cmbPartOfSpeech->currentText()
                ),
                leDefinition->text()
        );
        update_widgets();

        leWord->clear();
        leDefinition->clear();
        cmbPartOfSpeech->setCurrentIndex(0);
        leWord->setFocus();
    }
}

/**
 * @brief
 *  Edits the currently highlighted word in the dictionary and updates it with
 *  current information from the "add" widgets.
 */
void DictEditWin::on_pbEdit_clicked(void)
{
    if (this->twWordBank->currentItem()) {
        int currentRow = twWordBank->currentIndex().row();
        qDebug() << "on_pbEdit_clicked(): "
                 << "currentRow == " << currentRow;

        _dictionary->itemAt(currentRow)->setWord(leWord->text());
        _dictionary->itemAt(currentRow)->setPos(LyDict::posFromName(
                    cmbPartOfSpeech->currentText()
        ));
        _dictionary->itemAt(currentRow)->setDefinition(leDefinition->text());

        qDebug() << "on_pbEdit_clicked(): "
                 <<  "_dictionary->itemAt(currentRow) == "
                 << _dictionary->itemAt(currentRow)->data();

        this->twWordBank->currentItem()->setData(0, 0, this->leWord->text());
        this->twWordBank->currentItem()->setData(1, 0, this->cmbPartOfSpeech->currentText());
        this->twWordBank->currentItem()->setData(2, 0, this->leDefinition->text());
    }
}

/**
 * @brief
 *  Removes the currently selected word from the dictionary.
 */
void DictEditWin::on_pbRemove_clicked(void)
{
    if (twWordBank->currentItem()) {
        int currentRow = twWordBank->currentIndex().row();
        _dictionary->removeAt(currentRow);
        qDebug() << "on_pbRemove_clicked(): "
                 <<  "currentRow == " << currentRow;
        delete twWordBank->currentItem();
    }
}
