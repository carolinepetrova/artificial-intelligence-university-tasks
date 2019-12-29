#define CATCH_CONFIG_MAIN
#include <cmath>

#include "catch.hpp"
#include "entries.h"
#include "id3.h"
#include "utils.h"

bool double_equals(double a, double b, double epsilon = 0.001) {
  return std::abs(a - b) < epsilon;
}

vector<vector<string>> generateTestData() {
  return {
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
}

const unordered_map<string, int> testDataAttributeStringToIdMap = {
    {"Outlook", 1}, {"Temperature", 2}, {"Humidity", 3}, {"Windy", 4}};

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
  id3::Entries entries{generateTestData()};

  auto attributeWithHighestInformationGain =
      entries.getAttributeWithHighestInformationGain();

  CAPTURE(attributeWithHighestInformationGain);
  REQUIRE(attributeWithHighestInformationGain ==
          testDataAttributeStringToIdMap.at("Outlook"));
}

TEST_CASE(
    "Generating subset of entries with given attribute value works correctly") {
  auto entries = id3::Entries{generateTestData()};
  auto subsetWithSunnyOutlook = id3::generateSubset(
      entries, testDataAttributeStringToIdMap.at("Outlook"), "Sunny");
  REQUIRE(subsetWithSunnyOutlook.getData() ==
          vector<vector<string>>{{"No", "Hot", "High", "Weak"},
                                 {"No", "Hot", "High", "Strong"},
                                 {"No", "Mild", "High", "Weak"},
                                 {"Yes", "Cool", "Normal", "Weak"},
                                 {"Yes", "Mild", "Normal", "Strong"}});

  // test if empty subset is created with invalid attribute value [Smunny]
  REQUIRE(id3::generateSubset(
              entries, testDataAttributeStringToIdMap.at("Outlook"), "Smunny")
              .isEmpty());
}

/**
 * The resulting tree can be seen in the file 'test_final_tree.png'
 */
TEST_CASE("Id3 algorithm generates correct final decision tree") {
  id3::ID3Algorithm algorithm;
  auto rootNode =
      algorithm.generateDecisionTree(id3::Entries{generateTestData()});

  cout << "PRINT CHILDREN\n";
  rootNode->printAttributeValuesToChildren();

  REQUIRE(get<id3::AttributeId>(rootNode->getValue()) ==
          testDataAttributeStringToIdMap.at("Outlook"));

  auto printNodes = [](vector<shared_ptr<id3::Node>> nodes) {
    for (auto nodePtr : nodes) {
      if (nodePtr->isLeaf()) {
        cout << "Leaf. Class: " << get<id3::Class>(nodePtr->getValue()) << endl;
      } else {
        cout << "Non-leaf. Attribute: "
             << get<id3::AttributeId>(nodePtr->getValue()) << endl;
      }
    }
  };

  // TEST FIRST LEVEL CHILDREN
  const auto firstLevelChildren = rootNode->getChildren();
  cout << "\n\n--------------\n";
  printNodes(firstLevelChildren);
  cout << "--------------\n\n";

  REQUIRE(firstLevelChildren.size() == 3);

  // one child should be leaf with class "Yes"
  auto itFirstLevelLeaf = find_if(
      firstLevelChildren.begin(), firstLevelChildren.end(),
      [](shared_ptr<id3::Node> child) {
        return child->isLeaf() && get<id3::Class>(child->getValue()) == "Yes";
      });

  REQUIRE(itFirstLevelLeaf != firstLevelChildren.end());
  REQUIRE(*itFirstLevelLeaf == rootNode->getChildrenMap()["Overcast"]);


  // one child shoud be non-leaf with attribute "humidity"
  auto itFirstLevelHumidity =
      find_if(firstLevelChildren.begin(), firstLevelChildren.end(),
              [](shared_ptr<id3::Node> child) {
                return !child->isLeaf() &&
                       get<id3::AttributeId>(child->getValue()) ==
                           testDataAttributeStringToIdMap.at("Humidity") -
                               1;  // -1 because we are with 1 less attribute
              });
  REQUIRE(itFirstLevelHumidity != firstLevelChildren.end());
  REQUIRE(*itFirstLevelHumidity == rootNode->getChildrenMap()["Sunny"]);

  // one child shoud be non-leaf with attribute "windy"
  auto itFirstLevelWindy =
      find_if(firstLevelChildren.begin(), firstLevelChildren.end(),
              [](shared_ptr<id3::Node> child) {
                return !child->isLeaf() &&
                       get<id3::AttributeId>(child->getValue()) ==
                           testDataAttributeStringToIdMap.at("Windy") -
                               1;  // -1 because we are with 1 less attribute
              });
  REQUIRE(itFirstLevelWindy != firstLevelChildren.end());
  REQUIRE((*itFirstLevelWindy) == rootNode->getChildrenMap()["Rainy"]);

  // TEST SECOND LEVEL CHILDREN
  const auto secondLevelChildren1 = (*itFirstLevelWindy)->getChildren();
  const auto secondLevelChildren2 = (*itFirstLevelHumidity)->getChildren();

  REQUIRE((*itFirstLevelWindy)->getChildren().size() == 2);
  REQUIRE((*itFirstLevelHumidity)->getChildren().size() == 2);

  REQUIRE((*itFirstLevelWindy)->getChildrenMap()["Weak"]->isLeaf());
  REQUIRE(get<id3::Class>(
              (*itFirstLevelWindy)->getChildrenMap()["Weak"]->getValue()) ==
          "Yes");

  REQUIRE((*itFirstLevelWindy)->getChildrenMap()["Strong"]->isLeaf());
  REQUIRE(get<id3::Class>(
              (*itFirstLevelWindy)->getChildrenMap()["Strong"]->getValue()) ==
          "No");
  // ----

  REQUIRE((*itFirstLevelHumidity)->getChildrenMap()["High"]->isLeaf());
  REQUIRE(get<id3::Class>(
              (*itFirstLevelHumidity)->getChildrenMap()["High"]->getValue()) ==
          "No");

  REQUIRE((*itFirstLevelHumidity)->getChildrenMap()["Normal"]->isLeaf());
  REQUIRE(
      get<id3::Class>(
          (*itFirstLevelHumidity)->getChildrenMap()["Normal"]->getValue()) ==
      "Yes");
}