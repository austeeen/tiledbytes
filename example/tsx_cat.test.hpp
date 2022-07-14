#include <iostream>
#include <tiledbytes.hpp>


int main(int argc, char **argv)
{
    tb::Tsx tsx;
    tb::load<tb::Tsx>("res/cat.tsx", tsx);

    printf("tsx: %s | tile size(%d, %d), total tiles: %d, columns: %d\n",
        tsx.name, tsx.tilewidth, tsx.tileheight, tsx.tilecount, tsx.columns);

    printf("  tile list: %d\n", (int) tsx.tilelist.size());

    printf("  image source: %s, size(%d,%d)\n", tsx.image.source, tsx.image.width, tsx.image.height);

    printf("  properties\n");
    for (auto& [name, prp] : tsx.properties) {
        printf("    %s: %s\n", name, prp.value);
    }

    if (tb::ERRCODE == tb::ERR::CODE::NONE) {
        printf("%s complete.\n", argv[0]);
    } else {
        printf("%s failed. error code %d\n", argv[0], tb::ERRCODE);
    }

    return tb::ERRCODE;
};
