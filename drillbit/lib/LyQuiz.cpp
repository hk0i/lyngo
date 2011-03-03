#include "LyQuiz.h"

/**
 * @brief
 *  Create a quiz with a title (name)
 */
LyQuiz::LyQuiz(QString quizTitle)
    : _current_question(0),
      _quiz_title(quizTitle)
{

}

LyQuiz::LyQuiz(void)
    : _current_question(0)
{

}

/**
 * @brief
 *  Create a quiz and load the questions from a LyDict dictionary.
 */
LyQuiz::LyQuiz(const LyDict &dictionary)
    : _current_question(0)
{
    loadDictionary(dictionary);
}

/**
 * @brief
 *  Creates quiz @ref LyQuestion "questions" from a dictionary
 */
void LyQuiz::loadDictionary(LyDict dictionary)
{
    int i = 0; // loop counter
    int wom = 0; // random number (0,1), decides if question will be word or meaning
    // generate questions based on the dictionary
    DEBUG_PRINT("Now setting dictionary ..."
            <<  "Dictionary count: " << dictionary.count()
    );
    for (i = 0; i < dictionary.count(); ++i) {
        wom = qrand() % 2;
        if (wom > 1) {
            _questions.append(LyQuestion(dictionary.itemAt(i)->word(),
                              dictionary.itemAt(i)->definition()
            ));
        }
        else {
            _questions.append(LyQuestion(dictionary.itemAt(i)->definition(),
                              dictionary.itemAt(i)->word()
            ));
        }
    }
}

void LyQuiz::setTitle(const QString &newTitle)
{
    _quiz_title = newTitle;
}

/**
 * @brief
 *  Restarts the quiz, resetting the current question to the beginning
 */
void LyQuiz::restart(void)
{
    _current_question = 0;
}

/**
 * @brief
 *  Randomizes the order of the questions in the quiz.
 */
void LyQuiz::randomize(void)
{
    int i = 0;      // loop counter
    int rnd = -1;    // random number
    // keep track of the indices that were already used.
    QList<int> usedIndices;
    this->seed();

    usedIndices.append(-1);

    for (i = 0; i < _questions.count(); ++i) {
        while (usedIndices.contains(rnd) && i < _questions.count() - 1)
            rnd = (qrand() % _questions.count()) - 1;
        _questions.swap(i, rnd);
        usedIndices.append(rnd);
    }
}

/**
 * @brief
 *  Randomly swaps the questions in the quiz with the answers
 */
void LyQuiz::randomSwap(void)
{
    int i = 0;      // loop counter
    int swap = 0;   // random number, determines if we should swap
    this->seed();

    for (i = 0 ; i < _questions.count(); ++i) {
        swap = qrand() % 2;
        if (swap == 1)
            _questions[i].swap();
    }
}


/**
 * @brief
 *  Returns the next question in the quiz and advances the current question
 *  counter.
 */
LyQuestion LyQuiz::next(void)
{
    // minus one to take into account that we will be incrementing it after.
    if (_current_question <= _questions.count() - 1)
        return _questions[_current_question++];
}

/**
 * @brief
 *  Returns the previous question in the quiz and rewinds the curent question
 *  counter.
 */
LyQuestion LyQuiz::prev(void)
{
    if (_current_question > 0 && _current_question < _questions.count())
        return _questions[_current_question--];
}

/**
 * @brief
 *  Returns the current question number; i.e., question 5
 */
int LyQuiz::currentQuestion(void) const
{
    return _current_question;
}

/**
 * @brief
 *  Returns the number of questions in the quiz.
 */
int LyQuiz::count(void) const
{
    return _questions.count();
}

/*##################### Private member functions */

/**
 * @brief
 *  Returns a random @ref LyQuestion "question" from the quiz
 */
LyQuestion *LyQuiz::random_question(void)
{
    int rnd = 0;
    if (_questions.count() > 0) {
        rnd = qrand() % _questions.count();
        return &_questions[rnd];
    }

    return NULL;
}


// HTML quiz generation functions

/**
 * @brief
 *  Returns a string containing a full HTML page with a form that is prepopulated
 *  with questions and answers from the quiz
 */
QString LyQuiz::quizHtml(void)
{
    QString html = HTML_TOP;
    int i = 0;

    if (!_quiz_title.isEmpty())
        html.replace("${PAGE_TITLE}", _quiz_title);
    else
        html.replace("${PAGE_TITLE}", "Untitled Quiz");

    html += HTML_FORM_START;
    for (i = 0; i < this->count(); ++i) {
        html += nextHtml();
    }
    html += HTML_FORM_END + QString(HTML_BOTTOM);

    return html;

}

QString LyQuiz::title(void) const { return this->_quiz_title; }

/**
 * @brief
 *  Returns the next question from the Quiz in HTML format
 */
QString LyQuiz::nextHtml(void)
{
    QString html;
    QString tmpHtml;
    LyQuestion cur;

    if (_current_question < _questions.count()) {
        cur = this->next();
        tmpHtml = HTML_QUESTION_START;
        tmpHtml.replace("${QUESTION_ID}", QString("q") + QString::number(_current_question));
        tmpHtml.replace("${QUESTION}", cur.question());
        html += tmpHtml + HTML_QUESTION_END;
    }
    return html;
}

/**
 * @brief
 *  Seeds the qrand() function
 */
void LyQuiz::seed(void)
{
    QTime now = QTime::currentTime();
    qsrand(now.msec());
}

/**
 * @brief
 *  Returns the answer from a random question in the quiz, useful for multiple
 *  choice quizzes.
 */
QString LyQuiz::randomAnswer(void)
{
    LyQuestion *tmp;
    tmp = this->random_question();
    return tmp->answer();
}
