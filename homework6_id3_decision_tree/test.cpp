#define CATCH_CONFIG_MAIN
#include <cmath>

#include "catch.hpp"
#include "utils.h"

bool double_equals(double a, double b, double epsilon = 0.001) {
  return std::abs(a - b) < epsilon;
}

TEST_CASE("Entropy is calculated correctly") {
  REQUIRE(id3::calculateEntropy({{"A", 4}, {"B", 2}, {"C", 1}, {"D", 1}}) ==
          1.75);
  REQUIRE(id3::calculateEntropy({{"A", 2}, {"B", 2}, {"C", 2}, {"D", 2}}) == 2);
  REQUIRE(id3::calculateEntropy({{"A", 2}}) == 0);
}

TEST_CASE("Average information entropy is calculated correctly") {
  REQUIRE(double_equals(
      id3::calculateAverageInformationEntropy(
          14,
          {{"value1", {5, 0.971}}, {"value2", {5, 0.971}}, {"value3", {4, 0}}}),
      0.693));
}