#ifndef TEST_TSX_SPIDER_HPP
#define TEST_TSX_SPIDER_HPP

#include <cxxtest/TestSuite.h>
#include <tiledbytes.hpp>
#include <map>


class TsxSpiderTest : public CxxTest::TestSuite {
    tb::Tsx tsx;
    const char *tsx_file;

public:
    TsxSpiderTest():
        tsx_file("res/spider.tsx")
    {
        tb::load<tb::Tsx>(tsx_file, tsx);
    }

    static TsxSpiderTest *createSuite() { return new TsxSpiderTest(); }
    static void destroySuite(TsxSpiderTest *tsx_suite) { delete tsx_suite; }

    void testHadError() {
        TS_ASSERT_EQUALS(tb::ERRCODE, tb::ERR::CODE::NONE);
    }

    void testMetaData() {
        TS_ASSERT_EQUALS(tsx.name, "spider");
        TS_ASSERT_EQUALS(tsx.tilewidth, 16);
        TS_ASSERT_EQUALS(tsx.tileheight, 16);
        TS_ASSERT_EQUALS(tsx.tilecount, 54);
        TS_ASSERT_EQUALS(tsx.columns, 9);
    }

    void testAllTilesCollected() {
        TS_ASSERT_EQUALS(tsx.tilelist.size(), (size_t) 54);
    }

    void testImageSource() {
        TS_ASSERT_EQUALS(tsx.image.source, "elthen/spider.png");
        TS_ASSERT_EQUALS(tsx.image.width, 144);
        TS_ASSERT_EQUALS(tsx.image.height, 96);
    }

    void testProperties() {
        evaluateProperty("config", "file", "spider.cfg");
        evaluateProperty("facing_right", "bool", "false");
    }

private:
    void evaluateProperty(const std::string name, const std::string type, const std::string value) {
        if (tsx.properties.count(name) == 0) {
            TS_FAIL("PROPERTY_MISSING: " + std::string(name));
        } else {
            auto& prp = tsx.properties.at(name);
            TS_ASSERT_EQUALS(prp.type, type);
            TS_ASSERT_EQUALS(prp.value, value);
        }
    }

};

#endif // TEST_TSX_SPIDER_HPP
