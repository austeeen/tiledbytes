#include <iostream>
#include <tiledbytes.hpp>


int main(int argc, char **argv)
{
    tb::Tmx tmx{"test"};
    tb::loadTmx("res/test.tmx", tmx);

    printf("tmx: %s | map size(%d, %d), tile size(%d, %d)\n",
        tmx.name, tmx.width, tmx.height, tmx.tilewidth, tmx.tileheight);

    printf("  properties\n");
    for (auto& [name, prp] : tmx.properties) {
        printf("    %s: %s\n", name, prp.value);
    }

    for (auto& [firstgid, tst] : tmx.tilesets) {
        printf("tileset [%d] %d -> %s\n", firstgid, tst.firstgid, tst.name);
    }

    for (auto& lyr : tmx.layers) {
        printf("layer [%d] %s\n", lyr.id, lyr.name);
    }

    if (tb::ERRCODE == tb::ERR::CODE::NONE) {
        printf("%s complete.\n", argv[0]);
    } else {
        printf("%s failed. error code %d\n", argv[0], tb::ERRCODE);
    }

    return tb::ERRCODE;
};
