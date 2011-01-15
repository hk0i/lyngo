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

        QString question(void);
        QString answer(void);

        void setQuestion(const QString&);
        void setAnswer(const QString&);

    private:

        QString _question;
        QString _answer;

};

#endif
