#include "LyQuestion.h"

LyQuestion::LyQuestion(void)
{

}

LyQuestion::LyQuestion(const QString &question,
                       const QString &answer)
    : _question(question),
      _answer(answer),
      _swapped(false)
{

}

LyQuestion& LyQuestion::operator = (const LyQuestion &rhs)
{
    if (this == &rhs)
        return *this;

    this->setQuestion(rhs.question());
    this->setAnswer(rhs.answer());

    return *this;
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
QString LyQuestion::question(void) const
{
    if (_swapped)
        return _answer;
    return _question;
}

/**
 * @brief
 *  Returns the answer
 */
QString LyQuestion::answer(void) const
{
    qDebug() << "Swapped = " << _swapped << '\n';
    if (!_swapped)
        return _answer;
    return _question;
}

/**
 * @brief
 *  Swaps the question with the answer
 */
void LyQuestion::swap(void)
{
    // QString tmp = _question;
    // _question = _answer;
    // _answer = tmp;
    _swapped = !_swapped;
}

bool LyQuestion::isSwapped(void)
{
    return _swapped;
}
