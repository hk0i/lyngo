#include <iostream>
#include <QtCore>
#include <LyDict.h>
#include <LyQuiz.h>

int main(int argc, const char **argv)
{
    LyDict dict;
    // checking new overloaded operators
    LyQuestion q(QString("This is the question?"), QString("This is the answer."));
    LyQuestion w = q;

    qDebug() << q.question() << q.answer();
    qDebug() << w.question() << w.answer();

    dict.load("../../lessons/spanish/text books/revista "
              "- conversasion sin barreras/cine prado.ldb");
    qDebug() << "dict count:" << dict.count();

    LyQuiz quiz(dict);
    LyQuestion q1 = quiz.next();
    qDebug() << q1.question();
    qDebug() << q1.answer();

    // rewind the questions by 1
    q1 = quiz.prev();

    // print out entire quiz
    qDebug() << quiz.quizHtml();

    return 0;
}
