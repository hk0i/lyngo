#ifndef LYQUIZ_H
#define LYQUIZ_H

#include <LyDict.h>
#include <LyQuestion.h>

#define HTML_TOP "<!DOCTYPE HTML>\n" \
    "<html>\n" \
    "    <head>\n" \
    "        <meta http-equiv=\"content-type\" content=\"text/html; charset=utf-8\">\n" \
    "        <title>${PAGE_TITLE}</title>\n" \
    "    </head>\n" \
    "    <body>\n"

#define HTML_BOTTOM "    </body>\n" \
    "</html>\n"

#define HTML_FORM_START "        <form action=\"#\" method=\"get\" accept-charset=\"utf-8\">\n"
#define HTML_FORM_END "        </form>\n"

#define HTML_QUESTION_START "            <div id=\"${QUESTION_ID}\" class=\"question\">\n" \
    "                <p>${QUESTION}</p>\n"
#define HTML_QUESTION_END "            </div>\n"

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
        LyQuiz(QString);
        LyQuiz(const LyDict&);
        // virtual ~LyQuiz (void);

        void loadDictionary(LyDict);
        void setTitle(const QString&);

        int  currentQuestion(void) const;
        int count(void) const;

        LyQuestion next(void);
        LyQuestion prev(void);

        QString title(void) const;
        QString nextHtml(void);
        // QString prevHtml(void);
        QString quizHtml(void);

    private:

        /// Title of the quiz
        QString _quiz_title;
        /** stores the index of the current question */
        int _current_question;
        /// @todo remove dictionary object, it has nothing to do with quizes,
        /// instead allow the quiz to be generated from a dictionary and load
        /// a dictionary into the questions
        // realistically speaking questions do not have to be just vocabulary
        // words and their associated meanings. When this change comes into play
        // _questions and _dictionary will have totally separate meanings.
        QList<LyQuestion> _questions;

        void populate_quiz(void);
        LyQuestion *random_question(void);
};

#endif
