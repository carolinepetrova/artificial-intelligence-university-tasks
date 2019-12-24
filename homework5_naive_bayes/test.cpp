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
