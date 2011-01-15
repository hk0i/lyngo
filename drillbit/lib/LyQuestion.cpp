#include "LyQuestion.h"

LyQuestion::LyQuestion(void)
{

}

LyQuestion::LyQuestion(const QString &question,
                       const QString &answer)
    : _question(question),
      _answer(answer)
{

}

/**
 * @brief
 *  Assigns a new question to the LyQuestion.
 */
void LyQuestion::setQuestion(const QString &newQuestion)
{
    _question = newQuestion;
}

/**
 * @brief
 *  Assigns a new answer to the LyQuestion
 */
void LyQuestion::setAnswer(const QString &newAnswer)
{
    _answer = newAnswer;
}

/**
 * @brief
 *  Returns the question
 */
QString LyQuestion::question(void)
{
    return _question;
}

/**
 * @brief
 *  Returns the answer
 */
QString LyQuestion::answer(void)
{
    return _answer;
}
