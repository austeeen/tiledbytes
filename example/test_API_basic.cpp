#include <iostream>
#include <tiledbytes.hpp>


int main(int argc, char **argv)
{
    tb::Tmx t{"test"};
    tb::loadTmx("res/test.tmx", t);

    if (tb::ERRCODE == tb::ERR::CODE::NONE) {
        printf("%s complete.\n", argv[0]);
    } else {
        printf("%s failed. error code %d\n", argv[0], tb::ERRCODE);
    }

    return tb::ERRCODE;
};
