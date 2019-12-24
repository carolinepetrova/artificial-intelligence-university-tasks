#define CATCH_CONFIG_MAIN
#include <cmath>
#include <sstream>

#include "catch.hpp"
#include "naive_bayes.h"

const string testFileContent =
    "republican,n,y,n,y,y,y,n,n,n,y,?,y,y,y,n,y\n"
    "republican,n,y,n,y,y,y,n,n,n,n,n,y,y,y,n,?\n"
    "democrat,?,y,y,?,y,y,n,n,n,n,y,n,y,y,n,n\n"
    "democrat,n,y,y,n,?,y,n,n,n,n,y,n,y,n,n,y\n"
    "democrat,n,?,y,n,y,y,n,y,n,n,y,n,n,n,n,?\n"
    "democrat,y,y,y,n,y,y,n,y,y,n,y,n,n,y,n,?\n"
    "democrat,n,y,y,y,y,y,n,n,n,n,n,y,y,y,n,?\n"
    "democrat,y,n,y,n,n,n,y,y,y,?,y,n,n,n,y,?\n"
    "democrat,?,?,n,n,?,y,?,n,n,n,y,y,n,y,n,?\n"
    "democrat,y,y,n,n,n,n,n,y,y,n,y,n,n,n,y,n\n"
    "republican,y,y,n,y,y,y,n,n,n,n,y,y,y,y,n,y\n"
    "republican,?,?,?,?,n,y,n,y,y,n,n,y,y,n,n,?\n"
    "democrat,y,y,?,?,?,y,n,n,n,n,y,n,y,n,n,y\n"
    "democrat,y,y,y,?,n,n,n,y,n,n,y,?,n,n,y,y\n"
    "democrat,y,y,y,n,y,y,n,y,n,n,y,n,y,n,y,y\n"
    "democrat,y,y,n,n,y,?,n,n,n,n,y,n,y,y,n,y\n"
    "democrat,n,y,y,n,y,y,n,y,n,n,n,n,n,n,n,y\n"
    "republican,n,y,n,y,?,y,n,n,n,y,n,y,y,y,n,n\n"
    "republican,n,y,n,y,y,y,n,?,n,n,?,?,?,y,n,?\n"
    "republican,n,y,n,y,y,y,n,n,n,y,y,y,y,y,n,n\n"
    "republican,?,n,y,y,n,y,y,y,y,y,n,y,n,y,n,y\n"
    "republican,n,y,n,y,y,y,n,n,n,y,n,y,?,y,n,n\n"
    "republican,y,y,n,y,y,y,n,n,n,y,n,y,y,y,n,y\n"
    "republican,n,n,n,y,y,y,n,n,n,n,n,y,y,y,n,y\n"
    "democrat,y,n,y,n,y,y,n,n,y,y,n,n,y,y,n,y\n"
    "democrat,n,n,n,y,y,y,n,n,n,n,y,y,y,y,n,n\n"
    "democrat,y,n,y,n,n,y,y,y,y,n,n,y,?,y,y,y\n"
    "republican,n,n,n,y,y,y,n,n,n,n,n,y,y,y,n,n\n"
    "republican,n,n,n,y,y,y,n,n,n,n,y,y,y,y,n,y\n"
    "democrat,y,n,y,n,n,y,y,y,y,y,y,n,n,n,n,y\n"
    "republican,n,n,n,y,y,y,n,n,n,y,n,y,y,y,n,y\n"
    "republican,y,y,y,y,y,y,y,y,n,y,?,?,?,y,n,y\n"
    "democrat,y,y,y,n,n,n,y,y,y,n,n,n,n,n,n,y\n"
    "democrat,n,y,y,n,n,y,y,y,?,y,n,n,n,n,n,y\n"
    "republican,y,y,n,y,y,y,n,n,n,y,n,n,y,y,n,y\n"
    "democrat,y,y,y,n,n,n,y,y,y,y,y,n,y,n,n,y\n"
    "democrat,y,y,y,n,n,n,y,y,n,y,n,n,n,n,n,y\n"
    "democrat,y,y,y,n,n,n,y,y,y,n,n,n,n,n,n,y\n"
    "republican,y,y,y,y,y,y,y,y,n,y,n,n,y,y,n,y\n"
    "democrat,n,y,y,n,y,y,y,y,n,n,y,n,y,n,y,y\n"
    "democrat,n,n,y,n,n,y,y,y,y,n,y,n,n,n,y,y\n"
    "democrat,n,y,y,n,n,y,y,y,y,n,y,n,n,y,y,y\n"
    "democrat,n,y,y,n,n,?,y,y,y,y,y,n,?,y,y,y\n"
    "democrat,n,n,y,n,n,n,y,y,n,y,y,n,n,n,y,?\n"
    "democrat,y,n,y,n,n,n,y,y,y,y,n,n,n,n,y,y\n"
    "republican,n,n,n,y,y,y,y,y,n,y,n,y,y,y,n,y\n"
    "democrat,?,?,?,n,n,n,y,y,y,y,n,n,y,n,y,y\n"
    "democrat,y,n,y,n,?,n,y,y,y,y,n,y,n,?,y,y\n"
    "republican,n,n,y,y,y,y,n,n,y,y,n,y,y,y,n,y\n"
    "democrat,n,n,y,n,n,n,y,y,y,y,n,n,n,n,n,y\n"
    "republican,n,?,n,y,y,y,n,n,n,n,y,y,y,y,n,y\n"
    "republican,n,n,n,y,y,y,?,?,?,?,n,y,y,y,n,y\n"
    "republican,n,y,n,y,y,y,n,n,n,y,n,y,y,y,?,n\n";

bool double_equals(double a, double b, double epsilon = 0.001) {
  return std::abs(a - b) < epsilon;
}

SCENARIO("Calculations of NaiveBayesClassifier are valid") {
  GIVEN("A test input data for the clasifier") {
    istringstream iss{testFileContent};
    const auto& [inputData, numberOfAttributes] =
        naivebayes::generateInputDataForNaiveBayesClassifier(iss);
    WHEN("The model gets trained with the input data") {
      naivebayes::NaiveBayesClassifier classifier{inputData,
                                                  numberOfAttributes};
      THEN(
          "The sum of conditional probabilities for all attributes' values "
          "given a class should be 1") {
        for (int classId = 0; classId <= 1; classId++) {
          for (int attributeId = 0; attributeId <= 15; attributeId++) {
            auto attributeValueToProbabilityMap =
                classifier.classToAttributeProbabilityMap[classId][attributeId];
            double sum{0};
            for (int attributeValue = 0; attributeValue <= 2;
                 attributeValue++) {
              sum += attributeValueToProbabilityMap[attributeValue];
            }
            CAPTURE(sum, naivebayes::classIdToStringMap.at(classId),
                    attributeId, classId,
                    naivebayes::attributeIdToStringMap.at(attributeId));
            REQUIRE(double_equals(sum, 1.0));
          }
        }
      }
    }
  }
}

TEST_CASE("Splitting to subsets is correct") {
  std::string testInput =
      "democrat,y,n,y,n,n,n,y,y,y,y,n,n,n,n,y,y\n"
      "republican,n,n,n,y,y,y,y,y,n,y,n,y,y,y,n,y\n"
      "democrat,?,?,?,n,n,n,y,y,y,y,n,n,y,n,y,y\n"
      "democrat,y,n,y,n,?,n,y,y,y,y,n,y,n,?,y,y\n"
      "republican,n,n,y,y,y,y,n,n,y,y,n,y,y,y,n,y\n"
      "democrat,n,n,y,n,n,n,y,y,y,y,n,n,n,n,n,y\n"
      "republican,n,?,n,y,y,y,n,n,n,n,y,y,y,y,n,y\n"
      "republican,n,n,n,y,y,y,?,?,?,?,n,y,y,y,n,y\n"
      "republican,n,y,n,y,y,y,n,n,n,y,n,y,y,y,?,n\n";

  istringstream iss{testInput};
  const auto& [inputData, numberOfAttributes] =
      naivebayes::generateInputDataForNaiveBayesClassifier(iss);

  auto subsets = naivebayes::splitIntoSubsets(inputData, 5);

  // we want 4 subsets with 2 elements, and the last one (5th) should have 1
  // element
  for (int i = 0; i < 4; i++) {
    REQUIRE(subsets[i].size() == 2);
  }

  REQUIRE(subsets.back().size() == 1);

  // ----------
  // we want 1 subset with 9 elements
  subsets = naivebayes::splitIntoSubsets(inputData, 1);
  REQUIRE(subsets.size() == 1);
  REQUIRE(subsets[0].size() == 9);

  // ----------
  // we want 2 subsets, the 1st one with 5 elements, the 2nd one with 4 elements
  subsets = naivebayes::splitIntoSubsets(inputData, 2);
  REQUIRE(subsets.size() == 2);
  REQUIRE(subsets[0].size() == 5);
  REQUIRE(subsets[1].size() == 4);

  // ----------
  // we want 3 subsets, each with 3 elements
  subsets = naivebayes::splitIntoSubsets(inputData, 3);
  REQUIRE(subsets.size() == 3);
  for_each(subsets.begin(), subsets.end(),
           [](const naivebayes::InputEntries& subset) {
             REQUIRE(subset.size() == 3);
           });
}