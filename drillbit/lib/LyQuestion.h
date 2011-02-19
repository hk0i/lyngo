#ifndef LYQUESTION_H
#define LYQUESTION_H

#include <QtCore>

/**
 * @brief
 *  A simple data structure that represents a question and answer.
 */
class LyQuestion
{
    public:
        LyQuestion(void);
        LyQuestion(const QString&, const QString&);

        QString question(void) const;
        QString answer(void) const;
        QString title(void) const;

        void setQuestion(const QString&);
        void setAnswer(const QString&);

        LyQuestion &operator = (const LyQuestion &rhs);

    private:

        QString _question;
        QString _answer;

};

#endif
