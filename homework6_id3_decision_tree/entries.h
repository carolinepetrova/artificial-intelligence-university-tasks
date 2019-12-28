#ifndef ENTRIES_H
#define ENTIRES_H

#include <algorithm>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils.h"

namespace id3 {

using namespace std;

class Entries {
 private:
  vector<vector<string>> data;

  /**
   * @brief get all possible classes from the data
   *
   * In each row of the csv formatted data, represented as vector<string>, the
   * 0th element is expected to correspond to the class
   */
  unordered_set<string> getClasses() const {
    unordered_set<string> result;
    for_each(data.begin(), data.end(),
             [&result](const auto& entry) { result.insert(entry[0]); });
    return result;
  }

  int countEntriesByAttributeValue(int attributeId,
                                   string attributeValue) const {
    int result = 0;
    for_each(data.begin(), data.end(), [&result](const auto& entry) {
      if (entry[attributeId] == attributeValue) result++;
    });
    return result;
  }

  unordered_set<string> getAllPossibleAttributeValues(int attributeId) const {
    unordered_set<string> result;
    for_each(data.begin(), data.end(), [&result](const auto& entry) {
      result.insert(entry[attributeId]);
    });
    return result;
  }

  /**
   * @brief calculate E(A=x), e.g. E(Outlook=sunny)
   */
  Entropy calculateAttributeEntropy(int attributeId,
                                    string attributeValue) const {
    // 1. Create dataset only from entries which have the given attribute value
    // 2. Map each class to number of entries which belong to the class
    // 3. Call utility function to do the math

    // ------------------------

    unordered_map<Class, EntriesCount> classToCountMap;

    // initialize map with zeros
    for (const auto& c : getClasses()) {
      classToCountMap[c] = 0;
    }

    // fill the map
    for_each(data.begin(), data.end(), [&classToCountMap](const auto& entry) {
      if (entry[attributeId] == attributeValue) {
        const string& currentClass = entry[0];
        classToCountMap[currentClass]++;
      }
    });

    return calculateEntropy(classToCountMap);
  }

 public:
  bool areAllEntriesWithSameClass() const { return getClasses().size() == 1; }
  bool isEmpty() const { return data.empty(); }

  AttributeId getAttributeWithHighestInformationGain() const {
    const int totalNumberOfEntries = data.size();

    // we will find the attribute which has the lowest average
    // information entropy - this corresponds to highest information gain
    int attributeWithHighestInformationGain;
    int lowestAverageInformationEntropy = 10000;

    // start from 1, because the 0th index belongs to the class
    for (int attributeId = 1; attributeId < data.size(); attributeId++) {
      unordered_map<string, pair<EntriesCount, Entropy>>
          attributeValueToEntriesCountAndEntropyPairMap;

      auto allPossibleAttributeValues =
          getAllPossibleAttributeValues(attributeId);

      for (const auto& attributeValue : allPossibleAttributeValues) {
        auto currentEntropy =
            calculateAttributeEntropy(attributeId, attributeValue);
        auto entriesWithCurrentAttributeValue =
            countEntriesByAttributeValue(attributeId, attributeValue);
        attributeValueToEntriesCountAndEntropyPairMap.insert(
            {attributeValue,
             {entriesWithCurrentAttributeValue, currentEntropy}});

        auto currentAverageInformationEntropy =
            calculateAverageInformationEntropy(
                totalNumberOfEntries,
                attributeValueToEntriesCountAndEntropyPairMap);

        if (currentAverageInformationEntropy <
            lowestAverageInformationEntropy) {
          attributeWithHighestInformationGain = attributeId;
          currentAverageInformationEntropy = lowestAverageInformationEntropy;
        }
      }
    }
  }
};

}  // namespace id3

#endif