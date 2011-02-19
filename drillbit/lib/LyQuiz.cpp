#include "LyQuiz.h"

LyQuiz::LyQuiz(QString quizTitle)
    : _current_question(0),
      _quiz_title(quizTitle)
{

}

LyQuiz::LyQuiz(void)
    : _current_question(0)
{

}

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
