#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "naive_bayes.h"

const string testFileContent = "republican,n,y,n,y,y,y,n,n,n,y,?,y,y,y,n,y\n"
                               "republican,n,y,n,y,y,y,n,n,n,n,n,y,y,y,n,?\n"
                               "democrat,?,y,y,?,y,y,n,n,n,n,y,n,y,y,n,n\n"
                               "democrat,n,y,y,n,?,y,n,n,n,n,y,n,y,n,n,y\n";

SCENARIO("Test input data is read properly")
{
    GIVEN("A test stream with input data")
    {
        istringstream testInputStream{testFileContent};
        WHEN("We create a map from the data in the input stream")
        {
            auto classesCnt = createStatisticsMapFromStream(testInputStream);
            THEN("Democrats who have said yes for the 0th attribute should be 0")
            {
                REQUIRE(classesCnt[Class::DEMOCRAT][0][AttributeValue::YES] == 0);
            }
            THEN("Republicans who have said yes for the 15th attribute should be 1")
            {
                REQUIRE(classesCnt[Class::REPUBLICAN][15][AttributeValue::YES] == 1);
            }
            THEN("Democrats who have indeterminate value for the 3rd attribute should be 1")
            {
                REQUIRE(classesCnt[Class::DEMOCRAT][3][AttributeValue::INDETERMINATE] == 1);
            }
        }
    }
}
