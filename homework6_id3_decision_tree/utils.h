#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <exception>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace id3 {

class InvalidSumOfProbabilitiesException : public std::exception {
 private:
  std::string m_strErrMsg;

 public:
  explicit InvalidSumOfProbabilitiesException(const std::string& strErrMsg)
      : m_strErrMsg{strErrMsg} {}
  virtual const char* what() const noexcept override {
    return m_strErrMsg.c_str();
  }
};

class InvalidNumberOfEntriesException : public std::exception {
 private:
  std::string m_strErrMsg;

 public:
  explicit InvalidNumberOfEntriesException(const std::string& strErrMsg)
      : m_strErrMsg{strErrMsg} {}
  virtual const char* what() const noexcept override {
    return m_strErrMsg.c_str();
  }
};

using EntriesCount = int;
using Entropy = double;

/**
 * @brief Calculate entropy for a given attribute
 *
 * @param probabilities - P(class 0) = probabilites[0], P(class 1) =
 * probabilities[1] and so on...
 *
 * The sum of the vector should be 1
 *
 * For example, if we have 3 shapes for an apple, and shape 0 has probability of
 * 0.5, then probabilites[0] = 0.5 The other 2 could be probabilites[1] = 0.3
 * and probabilites[2] = 0.2
 *
 * @return the entropy
 *
 * @throw InvalidVectorOfProbabilitiesException if the sum of the probabilities
 * is not 1
 */
Entropy calculateEntropy(const vector<double>& probabilities) {
  double sumOfProbabilites = 0;
  for (auto probability : probabilities) {
    sumOfProbabilites += probability;
  }

  if (sumOfProbabilites != 1) {
    throw InvalidSumOfProbabilitiesException(
        "Sum of all probabilites is not 1!");
  }

  Entropy entropy = 0;
  for (auto probability : probabilities) {
    entropy -= probability * log2(probability);
  }
  return entropy;
}

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
        attributeValueToEntriesCountAndEntropyMap) {
  Entropy averageInformationEntropy = 0;

  for (const auto& [attributeValue, entriesCountAndEntropyPair] :
       attributeValueToEntriesCountAndEntropyMap) {
    const auto& [entriesCount, entropy] = entriesCountAndEntropyPair;
    if (entriesCount > totalNumberOfEntries) {
      stringstream error;
      error << "The number of entries for attribute value [" << attributeValue
            << "] is [" << entriesCount
            << "] which is higher than the total number of entries ["
            << totalNumberOfEntries << "].";
      throw InvalidNumberOfEntriesException(error.str());
    }

    averageInformationEntropy +=
        (static_cast<double>(entriesCount) / totalNumberOfEntries) * entropy;
  }
  return averageInformationEntropy;
}

}  // namespace id3

#endif
