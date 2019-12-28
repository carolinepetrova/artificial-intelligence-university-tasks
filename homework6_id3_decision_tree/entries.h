#ifndef ENTRIES_H
#define ENTRIES_H

#include <algorithm>
#include <iostream>
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

 public:
  Entries(const vector<vector<string>>& entries);

  bool areAllEntriesWithSameClass() const;
  bool isEmpty() const;

  AttributeId getAttributeWithHighestInformationGain() const;

 private:
  /**
   * Helper methods
   */

  /**
   * @brief get all possible classes from the data
   *
   * In each row of the csv formatted data, represented as vector<string>, the
   * 0th element is expected to correspond to the class
   */
  unordered_set<string> getClasses() const;

  int countEntriesByAttributeValue(int attributeId,
                                   string attributeValue) const;

  unordered_set<string> getAllPossibleAttributeValues(int attributeId) const;
  Entropy calculateAttributeAverageInformationEntropy(int attributeId) const;

  /**
   * @brief calculate E(A=x), e.g. E(Outlook=sunny)
   */
  Entropy calculateAttributeEntropy(int attributeId,
                                    string attributeValue) const;
};

}  // namespace id3

#endif