#include "LyQuiz.h"

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
        DEBUG_PRINT("wom: " << wom);
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
    if (_questions.count() > 0) {
        rnd = qrand() % _questions.count();
        return &_questions[rnd];
    }
}
