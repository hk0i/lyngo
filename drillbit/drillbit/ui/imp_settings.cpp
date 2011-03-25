#include "imp_settings.h"

SettingsWin::SettingsWin(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    connect(this, SIGNAL(accepted(void)), SLOT(write_settings(void)));
    read_settings();
}

/**
 * @brief
 *  Writes QSetting preferences
 */
void SettingsWin::write_settings(void)
{
        qDebug() << "Writing configuration " << _settings.fileName() << "...";
        // General
        _settings.beginGroup("General");
            _settings.setValue("load_previous_on_startup",
                    chkLoadPreviousOnStartup->checkState());
        _settings.endGroup();

        // Questions
        _settings.beginGroup("Questions");
            _settings.setValue("allow_mistakes",
                    chkAllowMistakes->checkState());
            _settings.setValue("randomize_questions",
                    chkRandomizeQuestions->checkState());
            _settings.setValue("randomly_swap_questions",
                    chkRandomlySwapQuestions->checkState());
        _settings.endGroup();
}

/**
 * @brief
 *  Reads in stored preferences from QSettings
 */
void SettingsWin::read_settings(void)
{
        _settings.beginGroup("General");
            chkLoadPreviousOnStartup->setCheckState(
                (Qt::CheckState)
                _settings.value("load_previous_on_startup",
                Qt::Unchecked
            ).toInt());
        _settings.endGroup();

        // Questions
        _settings.beginGroup("Questions");
            chkAllowMistakes->setCheckState(
                (Qt::CheckState)
                _settings.value("allow_mistakes",
                    Qt::Unchecked
                ).toInt());
            chkRandomizeQuestions->setCheckState(
                (Qt::CheckState)
                _settings.value("randomize_questions",
                    Qt::Unchecked
                ).toInt());
            chkRandomlySwapQuestions->setCheckState(
                (Qt::CheckState)
                _settings.value("randomly_swap_questions",
                    Qt::Unchecked
                ).toInt());
        _settings.endGroup();
}
