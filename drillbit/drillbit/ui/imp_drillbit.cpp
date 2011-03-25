#include "imp_drillbit.h"

DrillbitWin::DrillbitWin(QWidget *parent)
    : QMainWindow(parent),
      _current_answer(0),
      _mistakes(0)
{
    setupUi(this);

    lblStatus = new QLabel(this);
    lblStatus->setText("Driller");
    statusbar->addPermanentWidget(lblStatus);

    _dlg_settings = 0;
    setWindowTitle(QCoreApplication::applicationName());

}

DrillbitWin::~DrillbitWin(void)
{
    if (_dlg_settings)
        delete _dlg_settings;
}

/**
 * @brief
 *  Performs a clean exit of the program
 */
void DrillbitWin::on_mnuFileExit_triggered(bool checked)
{
    QCoreApplication::quit();
}

/**
 * @brief
 *  Displays preferences dialog
 */
void DrillbitWin::on_mnuEditPreferences_triggered(bool checked)
{
    int accept = 0;
    if (!_dlg_settings)
        _dlg_settings = new SettingsWin(this);

    accept = _dlg_settings->exec();
}

/**
 * @brief
 *  Loads a dictionary into the quiz and begins the quiz
 */
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
        install_preferences();
        _mistakes = 0;
        update_title(true);
        next_question();
        update_statusbar();
    }
}


/**
 * @brief
 *  Sets up the ui for the next question by loading the question and answers.
 */
void DrillbitWin::next_question(void)
{
    QStringList answers;
    QString     tmpAnswer;
    int         i = 0;      // loop counter

    //enable widgets
    this->enable_all_buttons();

    // check if we hit the end of the quiz
    if (_quiz.currentQuestion() >= _quiz.count())
        return;

    // next Question & Answer pair for quiz.
    LyQuestion q = _quiz.next();

    do {
        tmpAnswer = _quiz.randomAnswer();
        if (!answers.contains(tmpAnswer)
                && tmpAnswer != q.answer()) {
            answers << tmpAnswer;
            i++;
        }
    } while(i < 3);

    // insert correct answer in randomly
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    _current_answer = qrand() % 4;
    answers.insert(_current_answer, q.answer());
    _current_answer++;

    qDebug() << "Question & Answer:";
    qDebug() << q.question() << q.answer();
    qDebug() << "Choices:";
    qDebug() << answers;
    qDebug() << "Correct answer:" << _current_answer;

    lblWord->setText(q.question());
    this->answers_to_buttons(answers);
    update_title(true);
}

/**
 * @brief
 *  Takes a QStringList of answers and applies them to the buttons in the order
 *  they appear in the list.
 */
void DrillbitWin::answers_to_buttons(QStringList answers)
{
    pbChoice1->setText(answers[0]);
    pbChoice2->setText(answers[1]);
    pbChoice3->setText(answers[2]);
    pbChoice4->setText(answers[3]);
}

void DrillbitWin::on_pbChoice1_clicked(void) { check_answer(pbChoice1); }
void DrillbitWin::on_pbChoice2_clicked(void) { check_answer(pbChoice2); }
void DrillbitWin::on_pbChoice3_clicked(void) { check_answer(pbChoice3); }
void DrillbitWin::on_pbChoice4_clicked(void) { check_answer(pbChoice4); }

/**
 * @brief
 *  Checks to see if the button pushed is the correct answer
 */
void DrillbitWin::check_answer(QPushButton *button)
{
    int choice = button->objectName().right(1).toInt();
    qDebug() << choice;

    button->clearFocus();

    if (_quiz.currentQuestion() >= _quiz.count())
        return;

    if (choice != _current_answer) {
        _mistakes++;
        if (_settings.value("Questions/allow_mistakes").toBool())
            next_question();
        else
            button->setEnabled(false);
    }
    else {
        //correct answer, next question
        this->next_question();
    }
    this->update_statusbar();
}

/**
 * @brief
 *  Enables all answer push buttons
 */
void DrillbitWin::enable_all_buttons(void)
{
    pbChoice1->setEnabled(true);
    pbChoice2->setEnabled(true);
    pbChoice3->setEnabled(true);
    pbChoice4->setEnabled(true);
}

/**
 * @brief
 *  Updates window title with some meaningful text
 */
void DrillbitWin::update_title(bool unitToo)
{
    QString title = _quiz.title();
    QString fullTitle = title;
    if (_quiz.title().isEmpty())
        title = "Untitled Quiz";

    fullTitle += " (" + QString::number(_quiz.currentQuestion()) + "/"
          +  QString::number(_quiz.count()) + ")";

    this->setWindowTitle(QCoreApplication::applicationName() + " - " + title);
    if (unitToo)
        lblUnit->setText(fullTitle);
    else
        lblUnit->setText(title);
}

void DrillbitWin::update_statusbar(void)
{
    QString     statusbarText;
    QTextStream statusbarStream(&statusbarText);

    statusbarStream << tr("Question: ")
                  << _quiz.currentQuestion()
                  << "/"
                  << _quiz.count()
                  << " "
                  << tr("Mistakes: ")
                  << _mistakes;
    lblStatus->setText(statusbarText);

}
/**
 * @brief
 *  Applies preferences that are required after file load
 *  (i.e., Question randomization)
 */
void DrillbitWin::install_preferences(void)
{
    if (_settings.value("Questions/randomize_questions").toBool())
        _quiz.randomize();
    if (_settings.value("Questions/randomly_swap_questions").toBool())
        _quiz.randomSwap();
}
