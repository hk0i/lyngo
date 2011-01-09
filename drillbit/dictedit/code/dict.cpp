#include "../code/lydict.h"
#include <iostream>

int main(int argc, const char *argv[])
{
    LyDict ld;

    ld.load("/home/gmcquillan/apps/pylyngo/lessons/no hay que complicar la felicidad.ldb");
    std::cout << "count:" << ld.count() <<std::endl;
    ld.save("/home/gmcquillan/test.ldb");

    return 0;
}
