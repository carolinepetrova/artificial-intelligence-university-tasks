#include "entries.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

namespace id3 {

using namespace std;

Entries::Entries() {}

Entries::Entries(const vector<vector<string>>& entries) : data{entries} {}

bool Entries::areAllEntriesWithSameClass() const {
  return getClasses().size() == 1;
}

bool Entries::isEmpty() const { return data.empty(); }

AttributeId Entries::getAttributeWithHighestInformationGain() const {
  if (data.empty() || areAllEntriesWithSameClass() == 1) {
    throw "Calling getAttributeWithHighestInformationGain() in an invalid context -"
          " either no distinct classes or empty dataset.";
  }

  const int totalNumberOfEntries = data.size();

  // we will find the attribute which has the lowest average
  // information entropy - this corresponds to highest information gain
  int attributeWithHighestInformationGain;
  int lowestAverageInformationEntropy = 10000;

  // start from 1, because the 0th index belongs to the class
  for (AttributeId attributeId = 1; attributeId < data[0].size();
       attributeId++) {
    cout << "\n---------------------------\nStarting calculations for "
            "attribute with id "
         << attributeId << endl;

    auto currentAverageInformationEntropy =
        calculateAttributeAverageInformationEntropy(attributeId);

    cout << "Average information entropy for the attribute is: "
         << currentAverageInformationEntropy << endl
         << "------------------------------------\n";

    if (currentAverageInformationEntropy < lowestAverageInformationEntropy) {
      attributeWithHighestInformationGain = attributeId;
      lowestAverageInformationEntropy = currentAverageInformationEntropy;
    }
  }

  return attributeWithHighestInformationGain;
}

unordered_set<string> Entries::getClasses() const {
  unordered_set<string> result;
  for_each(data.begin(), data.end(),
           [&result](const auto& entry) { result.insert(entry[0]); });
  return result;
}

int Entries::countEntriesByAttribute(int attributeId,
                                     string attributeValue) const {
  int result = 0;
  for_each(data.begin(), data.end(), [&](const vector<string>& entry) {
    if (entry[attributeId] == attributeValue) result++;
  });
  return result;
}

unordered_set<string> Entries::getAllPossibleAttributeValues(
    int attributeId) const {
  unordered_set<string> result;
  for_each(data.begin(), data.end(), [&](const vector<string>& entry) {
    result.insert(entry[attributeId]);
  });
  return result;
}

Entropy Entries::calculateAttributeAverageInformationEntropy(
    int attributeId) const {
  const int totalNumberOfEntries = data.size();

  unordered_map<string, pair<EntriesCount, Entropy>>
      attributeValueToEntriesCountAndEntropyPairMap;

  auto allPossibleAttributeValues = getAllPossibleAttributeValues(attributeId);

  cout << "All possible values are: \n";
  for (const auto& attributeValue : allPossibleAttributeValues) {
    cout << attributeValue << " ";
  }
  cout << endl;

  for (const auto& attributeValue : allPossibleAttributeValues) {
    auto currentEntropy =
        calculateAttributeEntropy(attributeId, attributeValue);
    auto entriesWithCurrentAttributeValue =
        countEntriesByAttribute(attributeId, attributeValue);
    attributeValueToEntriesCountAndEntropyPairMap.insert(
        {attributeValue, {entriesWithCurrentAttributeValue, currentEntropy}});
  }

  return calculateAverageInformationEntropy(
      totalNumberOfEntries, attributeValueToEntriesCountAndEntropyPairMap);
}

Entropy Entries::calculateAttributeEntropy(int attributeId,
                                           string attributeValue) const {
  // 1. Create dataset only from entries which have the given attribute value
  // 2. Map each class to number of entries which belong to the class in the
  // dataset
  // 3. Call utility function to do the math

  // ------------------------

  unordered_map<Class, EntriesCount> classToCountMap;

  // initialize map with zeros
  for (const auto& c : getClasses()) {
    classToCountMap[c] = 0;
  }

  // fill the map
  for_each(data.begin(), data.end(), [&](const vector<string>& entry) {
    if (entry[attributeId] == attributeValue) {
      const string& currentClass = entry[0];
      classToCountMap[currentClass]++;
    }
  });

  return calculateEntropy(classToCountMap);
}

vector<vector<string>> Entries::getData() const { return data; }

Class Entries::getMostCommonClass() const {
  cout << "getMostCommonClass()\n";
  if (isEmpty()) {
    throw "Calling getMostCommonClass() on empty entries.";
  }

  unordered_map<Class, EntriesCount> classToCountMap;

  // initialize map with zeros
  for (const auto& c : getClasses()) {
    classToCountMap[c] = 0;
  }

  // fill the map
  for_each(data.begin(), data.end(),
           [&classToCountMap](const vector<string>& entry) {
             const auto& currentClass = entry[0];
             classToCountMap[currentClass]++;
           });

  Class mostCommonClass;
  int maxCount = -5000;

  for (const auto& [cl, count] : classToCountMap) {
    cout << "{" << cl << " -> " << count << "}\n";

    if (count > maxCount) {
      maxCount = count;
      mostCommonClass = cl;
    }
  }

  cout << "getMostCommonClass() end\n";

  return mostCommonClass;
}

}  // namespace id3
