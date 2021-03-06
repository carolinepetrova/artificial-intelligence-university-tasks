#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace id3 {

class Entries;

class InvalidNumberOfEntriesException : public std::exception {
 private:
  std::string m_strErrMsg;

 public:
  explicit InvalidNumberOfEntriesException(const std::string& strErrMsg);
  virtual const char* what() const noexcept override;
};

class EmptyEntriesException : public std::exception {
 private:
  std::string m_strErrMsg;

 public:
  explicit EmptyEntriesException(const std::string& strErrMsg);
  virtual const char* what() const noexcept override;
};

using AttributeId = int;
using AttributeValue = string;
using EntriesCount = int;
using Entropy = double;
using Class = string;

/**
 * @brief calculate entropy for some dataset
 *
 * @param data - maps class to number of entries with this class
 *
 * For example, if we have the sequence of classes A A A A B B C D,
 * we have P(A) = 1/2, P(B) = 1/4, P(C) = P(D) = 1/8
 *
 * The data unordered_map in this example will be this:
 * {"A" -> 4}, {"B" -> 2}, {"C" -> 1}, {"D" -> 1}
 *
 * The entropy will be:
 * -1/2*log2(1/2) - 1/4*log2(1/4) - 1/8*log2(1/8) - 1/8*log2(1/8) =
 * 1/2 + 1/2 + 3/8 + 3/8 = 1 + 3/4 = 1.75
 *
 */
Entropy calculateEntropy(unordered_map<Class, EntriesCount> data);

// clang-format off
/**
 * @brief calculate average information entropy for a given attribute
 *
 * For example, let's say we have an attribute 'outlook' which has 3 values - rainy,
 * overcast and sunny.
 * The average information entropy I(outlook) =
 * (number of entries with rainy outlook / total number of entries) * entropy(Outlook = rainy) +
 * (number of entries with overcast outlook / total number of entries) * entropy(Outlook = overcast) +
 * (number of entries with sunny outlook / total number of entries) * entropy(Outlook = sunny)
 *
 * @param totalNumberOfEntries - the total number of entries
 * @param attributeValueToEntriesCountAndEntropyMap - in this map, the keys correspond to the
 * possible attribute values (hence the size of the map corresponds to the total
 * number of possible values for an attribute); the value for a given key (which is a pair)
 * gives information about how many entries are there with the given attribute value
 * and what is the entropy for that specific attribute value
 *
 * @return the average information entropy
 * @throw InvalidNumberOfEntriesException if number of entries for specific attribute value is higher than
 * the total number of entries
 */
// clang-format on
Entropy calculateAverageInformationEntropy(
    int totalNumberOfEntries,
    const unordered_map<string, pair<EntriesCount, Entropy>>&
        attributeValueToEntriesCountAndEntropyMap);

/**
 * @brief generate subset of entries with specific attribute value
 */
Entries generateSubset(const Entries& entries, int attributeId,
                       const string& attributeValue);

}  // namespace id3

#endif
