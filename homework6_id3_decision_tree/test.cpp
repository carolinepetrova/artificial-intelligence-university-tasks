#define CATCH_CONFIG_MAIN
#include <cmath>

#include "catch.hpp"
#include "entries.h"
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

TEST_CASE("Average information entropy should be calculated correctly") {
  REQUIRE(double_equals(
      id3::calculateAverageInformationEntropy(
          14,
          {{"value1", {5, 0.971}}, {"value2", {5, 0.971}}, {"value3", {4, 0}}}),
      0.693));
}

TEST_CASE(
    "The attribute with highest information gain should be calculated "
    "correctly") {
  const vector<vector<string>> data = {
      {"No", "Sunny", "Hot", "High", "Weak"},
      {"No", "Sunny", "Hot", "High", "Strong"},
      {"Yes", "Overcast", "Hot", "High", "Weak"},
      {"Yes", "Rainy", "Mild", "High", "Weak"},
      {"Yes", "Rainy", "Cool", "Normal", "Weak"},
      {"No", "Rainy", "Cool", "Normal", "Strong"},
      {"Yes", "Overcast", "Cool", "Normal", "Strong"},
      {"No", "Sunny", "Mild", "High", "Weak"},
      {"Yes", "Sunny", "Cool", "Normal", "Weak"},
      {"Yes", "Rainy", "Mild", "Normal", "Weak"},
      {"Yes", "Sunny", "Mild", "Normal", "Strong"},
      {"Yes", "Overcast", "Mild", "High", "Strong"},
      {"Yes", "Overcast", "Hot", "Normal", "Weak"},
      {"No", "Rainy", "Mild", "High", "Strong"},
  };

  id3::Entries entries{data};

  auto attributeWithHighestInformationGain =
      entries.getAttributeWithHighestInformationGain();

  CAPTURE(attributeWithHighestInformationGain);
  REQUIRE(entries.getAttributeWithHighestInformationGain() ==
          1);  // entry[1] is the Outlook attribute
}