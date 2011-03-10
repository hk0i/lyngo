#include "LyGrade.h"

LyGrade::LyGrade(void)
    : _correct_answers(0),
      _total_questions(-1)
{

}

LyGrade::LyGrade(int correct, int total)
    : _correct_answers(correct),
      _total_questions(total)
{

}

/**
 * @brief
 *  Calculates a percentage grade based on the arguments passed to the function.
 */
double LyGrade::calculateGrade(int correct, int total)
{
    double result = 0.0;
    //never divide by zero
    if (total > 0)
        result = (correct * 100.0) / total;
    return result;
}
