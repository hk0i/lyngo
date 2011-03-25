#ifndef IMP_SETTINGS_H
#define IMP_SETTINGS_H

#include <QtGui>
#include <QSettings>

#include "ui_settings.h"

class SettingsWin : public QDialog, private Ui::SettingsWin
{
    Q_OBJECT

    public:
        SettingsWin(QWidget *parent = 0);

    private slots:
        void write_settings(void);

    private:
        QSettings _settings;

        void read_settings(void);


};

#endif
