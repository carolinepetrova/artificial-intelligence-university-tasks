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

  /**
   * Example:
   * If the function returns vector 'probabilities' with values {0.2, 0.3, 0.5},
   * this means that the attribute has 3 possible values;
   * The 1st value of the attribute has probability of occuring 0.2, i.e.
   * probabilites[0] = 0.2; same for the 2 other possible values of the
   * attribute - probabilities[1] = 0.3, probabilities[2] = 0.5
   */
  vector<double> calculateProbabilityForEachAttributeValue(int attributeId) {
    vector<double> probabilites;

    unordered_set<string> possibleAttributeValues =
        getAllPossibleAttributeValues(attributeId);

    for (const auto& attributeValue : possibleAttributeValues) {
      probabilites.push_back(
          calculateProbabilityForAttributeValue(attributeId, attributeValue));
    }
  }

  unordered_set<string> getAllPossibleAttributeValues(int attributeId) {
    unordered_set<string> result;
    for_each(data.begin(), data.end(), [&result](const auto& entry) {
      result.insert(entry[attributeId]);
    });
    return result;
  }

  double calculateProbabilityForAttributeValue(int attributeId,
                                               string attributeValue) {
    int totalEntriesWithGivenAttributeValue = 0;
    for (const auto& entry : data) {
      if (entry[attributeId] == attributeValue)
        ++totalEntriesWithGivenAttributeValue;
    }

    return static_cast<double>(totalEntriesWithGivenAttributeValue) /
           data.size();
  }

 public:
  bool areAllEntriesWithSameClass() const { return getClasses().size() == 1; }
  bool isEmpty() const { return data.empty(); }

  int getAttributeWithHighestInformationGain() const {
    const int totalNumberOfEntries = data.size();

    // we will find the attribute which has the lowest average
    // information entropy - this corresponds to highest information gain
    int attributeWithHighestInformationGain;
    int lowestEntropy = 10000;

    // start from 1, because the 0th index belongs to the class
    for (int attributeId = 1; attributeId < data.size(); attributeId++) {
        
    }
  }
};

}  // namespace id3

#endif