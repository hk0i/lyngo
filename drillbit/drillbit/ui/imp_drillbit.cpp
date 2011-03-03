#include "imp_drillbit.h"

DrillbitWin::DrillbitWin(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

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
    }

    this->update_title(true);
    this->next_question();
}


/**
 * @brief
 *  Sets up the ui for the next question by loading the question and answers.
 * @todo
 *  Possible bug: Choice D may never become a correct answer.
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
 *  they appear.
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

void DrillbitWin::check_answer(QPushButton *button)
{
    int choice = button->objectName().right(1).toInt();
    qDebug() << choice;

    if (choice == _current_answer) {
        //correct answer, next question
        this->next_question();
    }
    else {
        button->setEnabled(false);
    }
}

void DrillbitWin::enable_all_buttons(void)
{
    pbChoice1->setEnabled(true);
    pbChoice2->setEnabled(true);
    pbChoice3->setEnabled(true);
    pbChoice4->setEnabled(true);
}

void DrillbitWin::update_title(bool unitToo)
{
    QString title = _quiz.title();
    QString fullTitle = title;
    if (_quiz.title().isEmpty())
        title = "Untitled Quiz";

    fullTitle += " (" + QString::number(_quiz.currentQuestion()) + "/"
          +  QString::number(_quiz.count()) + ")";

    this->setWindowTitle(tr("Lyngo Drillbit - ") + title);
    if (unitToo)
        lblUnit->setText(fullTitle);
    else
        lblUnit->setText(title);
}
