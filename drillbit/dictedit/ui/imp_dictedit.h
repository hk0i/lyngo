#include <QtGui>
#include "ui_dictedit.h"
#include "code/lydict.h"

class DictEditWin : public QMainWindow, private Ui::DictEditWin
{
    Q_OBJECT

    public:
        DictEditWin(QWidget *parent = 0);

    private slots:
        void on_mnuOpen_triggered(bool);

    private:
        void update_widgets(void);

        LyDict *_dictionary;
};
