#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "utils.h"

TEST_CASE("Entropy is calculated correctly") {
  REQUIRE(id3::calculateEntropy({0.5, 0.25, 0.125, 0.125}) == 1.75);
  REQUIRE(id3::calculateEntropy({0.25, 0.25, 0.25, 0.25}) == 2);
  REQUIRE(id3::calculateEntropy({1}) == 0);
  REQUIRE_THROWS_AS(id3::calculateEntropy({0.5, 0.6}),
                    id3::InvalidSumOfProbabilitiesException);
}