#!/usr/bin/env bash

usage () {
    echo \
"run_test.sh

./run_test.sh [OPTIONS]+

description:
    this script builds and runs all tests. Does NOT build the TiledBytes library.

    ** providing no options is equivalent to setting 'b' and 'u'

options:
    b    | build regularly
    c    | clear all build files first, then build the app
    u    | include unit tests [DEFAULT]
    s    | include the samples
    h    | display this help page"
}

cwd=$(pwd)

quit() {
    if [[ $cwd != $PWD ]]; then
        cd $cwd
    fi
    exit $1
}

errcheck() {
    if [[ $1 -ne 0 ]]; then
        echo $2
        quit 1
    fi
}

if [[ $(basename "$cwd") != "test" ]]; then
    if [[ $(basename "$cwd") != "tiledbytes" ]]; then
        echo "Fatal: Not in a Tiled Bytes source tree"
        exit 1
    fi
    cd test
    errcheck $? "Fatal: could not 'cd' to test/ directory"
fi

DEPS_DIR="../deps"

GCC="g++ -Wall -ggdb3 -std=c++17"
CXX_TEST="${DEPS_DIR}/cxxtest"
TEST_LIB="../build/tiledbytes/"
TB_INC="../tiledbytes/include"
TB_LIB="TiledBytes"

MAIN_TEST="main.tests"
FILE_PTRN="*.test.*"

DO_BUILD=0
DO_CLEAN=0

UNIT_SRCS="./units"
SMPL_SRCS="./samples"
ALL_SRCS=""

args=($(echo $1 | grep -o .))
shift

for c in "${args[@]}"; do
    case $c in
        b)
            DO_BUILD=1;;
        c)
            DO_BUILD=1;
            DO_CLEAN=1;;
        u)
            ALL_SRCS="$ALL_SRCS $UNIT_SRCS/$FILE_PTRN";;
        s)
            ALL_SRCS="$ALL_SRCS $SMPL_SRCS/$FILE_PTRN";;
        h)
            usage; quit 0;;
        *)
            echo "bad arg: $c";;
  esac
done

if [[ ${ALL_SRCS} -eq "" ]]; then
    ALL_SRCS="$UNIT_SRCS/$FILE_PTRN"
fi

if [[ $DO_CLEAN -eq 1 ]]; then
    eval "rm ./${MAIN_TEST}.cpp ./${MAIN_TEST}.app"
    errcheck $? "Fatal: Could not clean build files"
fi

if [[ $DO_BUILD -eq 1 ]]; then
    eval "${CXX_TEST}/bin/cxxtestgen --error-printer -o ./${MAIN_TEST}.cpp ${ALL_SRCS}"
    errcheck $? "Fatal: Could not generate tests"
# ../build/tiledbytes/libTiledBytes.a
    eval "$GCC -L${TEST_LIB} -I${TB_INC} -I${CXX_TEST} -o ./${MAIN_TEST}.app ./${MAIN_TEST}.cpp -l${TB_LIB}"
    errcheck $? "Fatal: Could not build tests"
fi

eval "./${MAIN_TEST}.app"
quit $?