#include <iostream>
#include <tiledbytes.hpp>


int main(int argc, char **argv)
{
    tb::Tmx t{"test"};
    tb::loadTmx("res/test.tmx", t);

    printf("%s complete.", argv[0]);
    return 0;
};
