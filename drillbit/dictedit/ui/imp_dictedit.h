#include <QtGui>
#include "ui_dictedit.h"
#include "code/lydict.h"

class DictEditWin : public QMainWindow, private Ui::DictEditWin
{
    Q_OBJECT

    public:
        DictEditWin(QWidget *parent = 0);
        ~DictEditWin();

    private slots:
        // menus
        void on_mnuOpen_triggered(bool);
        void on_mnuSave_triggered(bool);
        void on_mnuSaveAs_triggered(bool);

        void on_twWordBank_currentItemChanged(QTreeWidgetItem*,
                QTreeWidgetItem*);

        // buttons
        void on_pbAdd_clicked(void);
        void on_pbEdit_clicked(void);

    private:
        void update_widgets(void);
        void update_window_title(void);

        LyDict *_dictionary;
        QString _current_file;
};
