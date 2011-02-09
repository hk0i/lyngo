#include "LyQuiz.h"

LyQuiz::LyQuiz(void)
    : _current_question(0)
{

}

LyQuiz::LyQuiz(const LyDict &dictionary)
    : _current_question(0)
{
    _dictionary = dictionary;
    populate_quiz();
}

/**
 * @brief
 *  Assigns a LyDict to the LyQuiz, this is mainly for use with the
 *  LyQuiz::LyQuiz() constructor that takes no LyDict argument.
 */
void LyQuiz::setDictionary(const LyDict &newDict)
{
    int i = 0; // loop counter
    int wom = 0; // random number (0,1), decides if question will be word or meaning
    _dictionary = newDict;

    // generate questions based on the dictionary
    for (i = 0; i < _dictionary.count(); ++i) {
        wom = qrand() % 2;
        if (wom > 1) {
            _questions.append(LyQuestion(_dictionary.itemAt(i)->word(),
                              _dictionary.itemAt(i)->definition()
            ));
        }
        else {
            _questions.append(LyQuestion(_dictionary.itemAt(i)->word(),
                              _dictionary.itemAt(i)->definition()
            ));
        }
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
    if (_current_question < _questions.count() - 1)
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
 *  Returns a pointer to the dictionary object being used by the quiz.
 */
LyDict *LyQuiz::dictionary(void)
{
    return &_dictionary;
}

/**
 * @brief
 *  Returns the current question number; i.e., question 5
 */
int LyQuiz::currentQuestion(void) const
{
    return _current_question;
}


/*##################### Private member functions */

/**
 * @brief
 *  Returns a random @ref LyQuestion "question" from the quiz
 */
LyQuestion *LyQuiz::random_question(void)
{
    int rnd = 0;
    DEBUG_PRINT("questions.count(): " << _questions.count());
    if (_questions.count() > 0) {
        rnd = qrand() % _questions.count();
        return &_questions[rnd];
    }
}

/**
 * @brief
 *  Generates the entire quiz and stores it locally to be accessed through the
 *  next() and prev() functions.
 */
void LyQuiz::populate_quiz(void)
{
    // keep track of the chosen questions so we don't reuse them.
    // QHash<LyQuestion*, bool> chosen;
    LyQuestion *q = random_question();
    if (q)
        DEBUG_PRINT(q->question().toStdString().c_str()
                << endl
                << q->answer().toStdString().c_str()
        );
}
