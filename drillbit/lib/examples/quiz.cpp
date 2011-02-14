#include <QtCore>
#include <LyDict.h>
#include <LyQuiz.h>

int main(int argc, const char **argv)
{
    LyDict dict;
    dict.load("../../lessons/spanish/text books/revista "
              "- conversasion sin barreras/cine prado.ldb");
    DEBUG_PRINT("dict count: " << dict.count());

    LyQuiz quiz(dict);

    return 0;
}
