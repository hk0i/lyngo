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

        void setQuestion(const QString&);
        void setAnswer(const QString&);
        void swap(void);

        bool isSwapped(void);

        LyQuestion &operator = (const LyQuestion &rhs);

    private:

        bool _swapped;

        QString _question;
        QString _answer;

};

#endif
