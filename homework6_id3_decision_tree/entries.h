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
  Entries();
  explicit Entries(const vector<vector<string>>& entries);

  vector<vector<string>> getData() const;

  bool areAllEntriesWithSameClass() const;
  bool isEmpty() const;

  AttributeId getAttributeWithHighestInformationGain() const;

  /**
   * @brief get all possible classes from the data
   *
   * In each row of the csv formatted data, represented as vector<string>, the
   * 0th element is expected to correspond to the class
   */
  unordered_set<string> getClasses() const;

  unordered_set<string> getAllPossibleAttributeValues(int attributeId) const;

  Class getMostCommonClass() const;

 private:
  /**
   * Helper methods
   */

  /**
   * @brief count the number of entries with specific attribute value
   */
  int countEntriesByAttribute(int attributeId, string attributeValue) const;

  Entropy calculateAttributeAverageInformationEntropy(int attributeId) const;

  /**
   * @brief calculate E(A=x), e.g. E(Outlook=sunny)
   */
  Entropy calculateAttributeEntropy(int attributeId,
                                    string attributeValue) const;
};

}  // namespace id3

std::ostream& operator<<(std::ostream& os, const id3::Entries& entries);

bool operator==(const id3::Entries& lhs, const id3::Entries& rhs);

#endif