#include <iostream>
#include <QtCore>
#include <LyDict.h>
#include <LyQuiz.h>

int main(int argc, const char **argv)
{
    LyDict dict;
    //checking new overloaded operators
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

    //rewind the questions by 1/test prev()
    q1 = quiz.prev();

    //print out entire quiz
    qDebug() << quiz.quizHtml();

    //test restart
    quiz.restart();

    //test randomize
    quiz.randomize();

    qDebug() << "randomize():";
    //print new quiz
    for (int i = 0; i < quiz.count(); ++i) {
        q1 = quiz.next();
        qDebug() << q1.question();
        qDebug() << q1.answer();
    }

    //restart quiz again
    quiz.restart();

    //randomly swap questions/answers
    quiz.randomSwap();

    qDebug() << "randomSwap():";
    //print new quiz
    for (int i = 0; i < quiz.count(); ++i) {
        q1 = quiz.next();
        qDebug() << q1.question();
        qDebug() << q1.answer();
    }

    qDebug() << "Random Answers:";
    for (int i = 0; i < 4; ++i)
        qDebug() << quiz.randomAnswer();

    return 0;
}
