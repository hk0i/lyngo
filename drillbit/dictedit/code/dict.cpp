#include "../code/lydict.h"
#include "../code/lyword.h"
#include <iostream>

int main(int argc, const char *argv[])
{
    LyDict ld;

    ld.load("../../lessons/spanish/text books/revista - conversasion sin barreras/cine prado.ldb");
    std::cout << "count:" << ld.count() <<std::endl;
    ld.save("/Users/grekkos/test.ldb");

    QStringList testing;
    testing << "one " << "1" << " two " << "2";
    std::cout << testing.join(QString(",")).toStdString().c_str();

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
              << apple.data().join(QString("\t")).toStdString().c_str();

    return 0;
}
