#include <QtCore>
#include <LyDict.h>
#include <LyQuiz.h>

int main(int argc, const char **argv)
{
    LyDict dict;
    dict.load("../lessons/spanish/text books/revista "
              "- conversacion sin barreras/cine prado.ldb");

    LyQuiz quiz(dict);

    return 0;
}
