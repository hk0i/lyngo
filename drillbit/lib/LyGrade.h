#ifndef LYGRADE_H
#define LYGRADE_H

/**
 * @brief
 *  Generates statistics and grades based on ratio of
 *  correct answers:incorrect answers.
 */
class LyGrade
{
    public:
        LyGrade(void);
        LyGrade(int, int);

        char gradeLetter(void);
        double grade(void);

        static double calculateGrade(int, int);

    private:

        int _correct_answers;
        int _total_questions;
};

#endif
