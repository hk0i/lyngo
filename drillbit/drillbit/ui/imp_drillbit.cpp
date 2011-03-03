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
    this->nextQuestion();
}


/**
 * @brief
 *  Sets up the ui for the next question by loading the question and answers.
 * @todo
 *  Possible bug: Choice D may never become a correct answer.
 */
void DrillbitWin::nextQuestion(void)
{
    QStringList answers;
    QString     tmpAnswer;
    int         i = 0;      // loop counter

    //enable widgets
    this->enableAllButtons();

    // next Question & Answer pair for quiz.
    LyQuestion q = _quiz.next();

    do {
        tmpAnswer = _quiz.randomAnswer();
        if (!answers.contains(tmpAnswer)) {
            answers << tmpAnswer;
            i++;
        }
    } while(i < 3);

    // insert correct answer in randomly
    QTime now = QTime::currentTime();
    qsrand(now.msec());
    _current_answer = qrand() % 3;
    answers.insert(_current_answer, q.answer());
    _current_answer++;

    qDebug() << "Question & Answer:";
    qDebug() << q.question() << q.answer();
    qDebug() << "Choices:";
    qDebug() << answers;
    qDebug() << "Correct answer:" << _current_answer;

    lblWord->setText(q.question());
    this->answersToButtons(answers);
}

/**
 * @brief
 *  Takes a QStringList of answers and applies them to the buttons in the order
 *  they appear.
 */
void DrillbitWin::answersToButtons(QStringList answers)
{
    pbChoice1->setText(answers[0]);
    pbChoice2->setText(answers[1]);
    pbChoice3->setText(answers[2]);
    pbChoice4->setText(answers[3]);
}

void DrillbitWin::on_pbChoice1_clicked(void) { checkAnswer(pbChoice1); }
void DrillbitWin::on_pbChoice2_clicked(void) { checkAnswer(pbChoice2); }
void DrillbitWin::on_pbChoice3_clicked(void) { checkAnswer(pbChoice3); }
void DrillbitWin::on_pbChoice4_clicked(void) { checkAnswer(pbChoice4); }

void DrillbitWin::checkAnswer(QPushButton *button)
{
    int choice = button->objectName().right(1).toInt();
    qDebug() << choice;

    if (choice == _current_answer) {
        //correct answer, next question
        this->nextQuestion();
    }
    else {
        button->setEnabled(false);
    }
}

void DrillbitWin::enableAllButtons(void)
{
    pbChoice1->setEnabled(true);
    pbChoice2->setEnabled(true);
    pbChoice3->setEnabled(true);
    pbChoice4->setEnabled(true);
}
