#ifndef __IMP_DRILLBIT_H
#define __IMP_DRILLBIT_H

#include <QtGui>
#include <LyQuiz.h>

#include "ui_drillbit.h"

class DrillbitWin : public QMainWindow, private Ui::DrillbitWin
{
    Q_OBJECT

    public:
        DrillbitWin(QWidget *parent = 0);

    private slots:
        //menus
        /*
        void on_mnuFileOpen_triggered(bool);
        */
        void on_mnuFileOpenVocabulary_triggered(bool);
        /*
        void on_mnuFileHtmlQuiz_triggered(bool);
        */
        void on_mnuFileExit_triggered(bool);

        // buttons
        void on_pbChoice1_clicked(void);
        void on_pbChoice2_clicked(void);
        void on_pbChoice3_clicked(void);
        void on_pbChoice4_clicked(void);

    private:

        // number of the correct answer for current question
        int _current_answer;

        void nextQuestion(void);

        void answersToButtons(QStringList);
        void checkAnswer(QPushButton*);
        void enableAllButtons(void);
        LyQuiz _quiz;
};

#endif

