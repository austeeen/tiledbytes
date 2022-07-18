#ifndef TEST_FILE_SEARCH_HPP
#define TEST_FILE_SEARCH_HPP

#include <cxxtest/TestSuite.h>
#include <tiledbytes.hpp>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;


class FileSearchTest : public CxxTest::TestSuite {
    tb::ResourceTable rsrcs;
    const char *rsrc_root;

public:
    FileSearchTest():
        rsrc_root("res/")
    {
        tb::search(rsrc_root, rsrcs);
    }

    static FileSearchTest *createSuite() { return new FileSearchTest(); }
    static void destroySuite(FileSearchTest *tsx_suite) { delete tsx_suite; }

    void testHadError() {
        TS_ASSERT_EQUALS(tb::ERRCODE, tb::ERR::CODE::NONE);
    }

    void testDiscovery() {
        for (auto& [type, filemap] : rsrcs) {
            if (filemap.empty()) {
                TS_FAIL("NO FILES OF TYPE " + toStr(type) + " WERE FOUND");
            }
        }
    }

    void testFileExtensions() {
        for (auto& [type, filemap] : rsrcs) {
            for (auto& [fn, fp] : filemap) {
                TS_ASSERT(fs::path(fp).extension() == toStr(type));
            }
        }
    }

private:
    const std::string toStr(tb::FileType t) {
        switch(t) {
            case tb::FileType::Tsx: { return ".tsx"; }
            case tb::FileType::Tmx: { return ".tmx"; }
            case tb::FileType::Img: { return ".png"; } // eventually support more image file formats
            default: { break; }
        }
        return "[INVALID FILE TYPE]";
    }
};

#endif // TEST_FILE_SEARCH_HPP
