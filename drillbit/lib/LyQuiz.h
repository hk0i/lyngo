#ifndef LYQUIZ_H
#define LYQUIZ_H

#include <LyDict.h>
#include <LyQuestion.h>

/**
 * @brief
 *  Generates quizzes from @ref LyDict "LyDicts".
 * @author
 *  Gregory McQuillan
 */
class LyQuiz
{
    public:
        LyQuiz(void);
        LyQuiz(const LyDict&);
        // virtual ~LyQuiz (void);

        void setDictionary(const LyDict&);
        int  currentQuestion(void) const;

        LyQuestion next(void);
        LyQuestion prev(void);

        LyDict *dictionary(void);

    private:
        /** stores the index of the current question */
        int _current_question;
        LyDict _dictionary;
        // realistically speaking questions do not have to be just vocabulary
        // words and their associated meanings. When this change comes into play
        // _questions and _dictionary will have totally separate meanings.
        QList<LyQuestion> _questions;

        void populate_quiz(void);
        LyQuestion *random_question(void);
};

#endif
