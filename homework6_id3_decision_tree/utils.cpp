#include "utils.h"

#include "entries.h"

namespace id3 {

InvalidNumberOfEntriesException::InvalidNumberOfEntriesException(
    const std::string& strErrMsg)
    : m_strErrMsg{strErrMsg} {}

const char* InvalidNumberOfEntriesException::what() const noexcept {
  return m_strErrMsg.c_str();
}

EmptyEntriesException::EmptyEntriesException(const std::string& strErrMsg)
    : m_strErrMsg{strErrMsg} {}

const char* EmptyEntriesException::what() const noexcept {
  return m_strErrMsg.c_str();
}

Entropy calculateEntropy(unordered_map<Class, EntriesCount> data) {
  cout << "\ncalculateEntropy() called with map: \n";
  for (const auto& [cl, entriesCount] : data) {
    cout << "{" << cl << " -> " << entriesCount << "}\n";
  }

  int totalNumberOfEntries = 0;
  for (const auto& [currentClass, entriesCount] : data) {
    totalNumberOfEntries += entriesCount;
  }

  Entropy entropy = 0;
  for (const auto& [currentClass, entriesCount] : data) {
    if (entriesCount != 0) {
      double probability =
          static_cast<double>(entriesCount) / totalNumberOfEntries;
      entropy -= probability * log2(probability);
    }
  }
  return entropy;
}

Entropy calculateAverageInformationEntropy(
    int totalNumberOfEntries,
    const unordered_map<string, pair<EntriesCount, Entropy>>&
        attributeValueToEntriesCountAndEntropyMap) {
  cout << "\ncalculateAverageInformationEntropy() called with "
          "totalNumberOfEntries = ["
       << totalNumberOfEntries << "] and map:\n";

  for (const auto& [attributeValue, entriesCountAndEntropyPair] :
       attributeValueToEntriesCountAndEntropyMap) {
    cout << "{" << attributeValue << " -> {" << entriesCountAndEntropyPair.first
         << ", " << entriesCountAndEntropyPair.second << "}}\n";
  }

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

Entries generateSubset(const Entries& entries, int attributeId,
                       const string& attributeValue) {
  vector<vector<string>> data = entries.getData();

  data.erase(remove_if(data.begin(), data.end(),
                       [&](const vector<string>& entry) {
                         return entry[attributeId] != attributeValue;
                       }),
             data.end());
  return Entries{data};
}

}  // namespace id3
