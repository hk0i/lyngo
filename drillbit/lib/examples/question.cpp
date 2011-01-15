#include <iostream>
#include <QtCore>
#include <LyQuestion.h>

void printQandA(LyQuestion q)
{
    std::cout << q.question().toStdString().c_str()
              << std::endl
              << q.answer().toStdString().c_str()
              << std::endl;
}

int main(int argc, const char **argv)
{
    LyQuestion q1;
    q1.setQuestion("What is the capital of New York?");
    q1.setAnswer("Albany");

    LyQuestion q2("What is the airspeed velocity of an unladen swallow?",
                  "African or European?");

    printQandA(q1);
    printQandA(q2);

    return 0;
}
