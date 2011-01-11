#include "../code/lydict.h"
#include "../code/lyword.h"
#include <iostream>

int main(int argc, const char *argv[])
{
    LyDict ld;

    ld.load("/home/gmcquillan/apps/pylyngo/lessons/no hay que complicar la felicidad.ldb");
    std::cout << "count:" << ld.count() <<std::endl;
    ld.save("/home/gmcquillan/test.ldb");

    LyWord apple(QString("Apple"),
                 QChar('n'),
                 QString("A red thing")
    );

    std::cout << "word: " << apple.word().toStdString().c_str()
              << " pos: " << apple.pos().toAscii()
              << "(" << apple.partOfSpeech().toStdString().c_str() << ")"
              << " meaning: " << apple.definition().toStdString().c_str()
              << "\n";

    std::cout << "For writing to file (data()): \n"
              << apple.data().join(QString("\t")).trimmed().toStdString().c_str();

    return 0;
}
