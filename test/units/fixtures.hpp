#ifndef TEST_FIXTURES_HPP
#define TEST_FIXTURES_HPP

#include <cxxtest/TestSuite.h>
#include <tiledbytes.hpp>
#include <map>


class TsxTest : public CxxTest::TestSuite {
    tb::Tsx tsx;
    const char *tsx_file;

public:
    TsxTest(const char *filepath):
        tsx_file(filepath)
    {
        tb::load<tb::Tsx>(tsx_file, tsx);
    }

    static TsxTest *createSuite() { return new TsxTest(); }
    static void destroySuite(TsxTest *tsx_suite) { delete tsx_suite; }

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

#endif // TEST_FIXTURES_HPP
