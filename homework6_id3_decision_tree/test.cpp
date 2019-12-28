#define CATCH_CONFIG_MAIN
#include <cmath>

#include "catch.hpp"
#include "utils.h"

bool double_equals(double a, double b, double epsilon = 0.001) {
  return std::abs(a - b) < epsilon;
}

TEST_CASE("Entropy is calculated correctly") {
  REQUIRE(id3::calculateEntropy({0.5, 0.25, 0.125, 0.125}) == 1.75);
  REQUIRE(id3::calculateEntropy({0.25, 0.25, 0.25, 0.25}) == 2);
  REQUIRE(id3::calculateEntropy({1}) == 0);
  REQUIRE_THROWS_AS(id3::calculateEntropy({0.5, 0.6}),
                    id3::InvalidSumOfProbabilitiesException);
}

TEST_CASE("Average information entropy is calculated correctly") {
  REQUIRE(double_equals(id3::calculateAverageInformationEntropy(
                            14, {{5, 0.971}, {5, 0.971}, {4, 0}}),
                        0.693));
}