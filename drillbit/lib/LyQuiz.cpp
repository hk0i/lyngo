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
    _dictionary = newDict;
}

/**
 * @brief
 *  Returns the next question in the quiz and advances the current question
 *  counter.
 */
LyQuestion LyQuiz::next(void)
{
    return _questions[_current_question++];
}

/**
 * @brief
 *  Returns the previous question in the quiz and rewinds the curent question
 *  counter.
 */
LyQuestion LyQuiz::prev(void)
{
    return _questions[_current_question--];
}

/**
 * @brief
 *  Returns a pointer to the dictionary object being used by the quiz.
 */
LyDict LyQuiz::dictionary(void)
{
    return _dictionary;
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
    int rnd = qrand() % _questions.count();
    return _questions[rnd];
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
    DEBUG_PRINT(q->question().toStdString().c_str()
            << endl
            << q->answer().toStdString().c_str()
    );
}
