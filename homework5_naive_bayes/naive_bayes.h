#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace naivebayes {

// What the classifier has to calculate is:
// input -> x1, ..., xN (attributes)
// output -> the most probable Ck for the input attributes - Ck with max
// P(Ck|x1,...,xN)

// Theory: The Ck with the largest P(Ck|x1,...,xN) is the Ck with the largest
// P(Ck)*P(x1|Ck)*...*P(xN|Ck)
// Hence the unordered_map structures in the class NaiveBayesClassifier

using Class = int;
using ClassId = int;
using Probability = double;
using AttributeId = int;
using Count = int;
using AttributeValue = int;
using NumberOfAttributes = int;
using InputEntries = vector<vector<int>>;

const unordered_map<ClassId, string> classIdToStringMap = {
    {0, "democrat"},
    {1, "republican"},
};

const unordered_map<AttributeId, string> attributeIdToStringMap = {
    {0, "HANDICAPPED_INFANTS"},
    {1, "WATER_PROJECT_COST_SHARING"},
    {2, "ADOPTION_OF_THE_BUDGET_RESOLUTION"},
    {3, "PHYSICIAN_FEE_FREEZE"},
    {4, "EL_SALVADOR_AID"},
    {5, "RELIGIOUS_GROUPS_IN_SCHOOLS"},
    {6, "ANTI_SATELLITE_TEST_BAN"},
    {7, "AID_TO_NICARAGUAN_CONTRAS"},
    {8, "MX_MISSILE"},
    {9, "IMMIGRATION"},
    {10, "SYNFUELS_CORPORATION_CUTBACK"},
    {11, "EDUCATION_SPENDING"},
    {12, "SUPERFUND_RIGHT_TO_SUE"},
    {13, "CRIME"},
    {14, "DUTY_FREE_EXPORTS"},
    {15, "EXPORT_ADMINISTRATION_ACT_SOUTH_AFRICA"},
};

const unordered_map<AttributeValue, string> attributeValueToStringMap = {
    {0, "YES"},
    {1, "NO"},
    {2, "INDETERMINATE"},
};

class NaiveBayesClassifier {
 public:
  // <class id, class probability>; <C,P(C)>
  unordered_map<ClassId, Probability> classToProbabilityMap;

  // <class id, <attribute id, <attribute value, probability>>> <-> <C,
  // <attribute x, <attribute x value, P(x=attributevalue|C)>>>
  unordered_map<
      ClassId,
      unordered_map<AttributeId, unordered_map<AttributeValue, Probability>>>
      classToAttributeProbabilityMap;

 private:
  void countAllClassesAndAttributes(
      const vector<vector<int>> &data, int numberOfAttributes,
      unordered_map<ClassId, Count> &classToCountMap,
      unordered_map<
          ClassId,
          unordered_map<AttributeId, unordered_map<AttributeValue, Count>>>
          &classToAttributeCountMap) {
    for (auto entry : data) {
      const int currentClass = entry[0];
      if (classToCountMap.find(currentClass) == classToCountMap.end()) {
        classToCountMap[currentClass] = 1;
        classToAttributeCountMap[currentClass] = {};
      } else {
        classToCountMap[currentClass] += 1;
      }

      for (int attributeId = 0; attributeId < numberOfAttributes;
           attributeId++) {
        const int attributeValue = entry[attributeId];
        auto &currentClassAttributeToCountMap =
            classToAttributeCountMap[currentClass][attributeId];
        if (currentClassAttributeToCountMap.find(attributeValue) ==
            currentClassAttributeToCountMap.end()) {
          currentClassAttributeToCountMap[attributeValue] = 1;
        } else {
          currentClassAttributeToCountMap[attributeValue] += 1;
        }
      }
    }
  }

  void calculcateProbabilityPerClassAndAttribute(
      const vector<vector<int>> &data, int numberOfAttributes) {
    cout << "calculcateProbabilityPerClassAndAttribute()\n";

    // count classes <C, total number of instances with class C>
    unordered_map<Class, Count> classToCountMap;

    // count attributes per class <C, <AttributeId, <AttributeValue, Count>>>
    // for example:
    // <class Democrat -> <HANDICAPPED_INFANTS -> {"yes" -> 69, "no" -> 23,
    // "indeterminate" -> 15},
    //                    <PHYSICIAN_FEE_FREEZE -> {"yes" -> 123, "no" -> 4,
    //                    "indeterminate" -> 67}>>
    unordered_map<ClassId, unordered_map<AttributeId,
                                         unordered_map<AttributeValue, Count>>>
        classToAttributeCountMap;

    countAllClassesAndAttributes(data, numberOfAttributes, classToCountMap,
                                 classToAttributeCountMap);

    for (auto &[currentClassId, attributeIdToCountMap] :
         classToAttributeCountMap) {
      cout << "\n--- Class " << classIdToStringMap.at(currentClassId) << "---"
           << endl;
      for (auto &[attributeId, attributeCountMap] : attributeIdToCountMap) {
        for (int attributeValue = 0; attributeValue <= 2; attributeValue++) {
          auto &probability =
              classToAttributeProbabilityMap[currentClassId][attributeId]
                                            [attributeValue];
          probability = static_cast<double>(attributeCountMap[attributeValue]) /
                        classToCountMap[currentClassId];

          cout << "Attribute " << attributeIdToStringMap.at(attributeId)
               << " P(x=" << attributeValueToStringMap.at(attributeValue)
               << "|C=" << classIdToStringMap.at(currentClassId)
               << ") = " << probability << endl;
        }
      }

      classToProbabilityMap[currentClassId] =
          static_cast<double>(classToCountMap[currentClassId]) / data.size();

      cout << "Class P(C=" << classIdToStringMap.at(currentClassId)
           << ") = " << classToProbabilityMap[currentClassId] << endl;
    }
  }

 public:
  // input: vector< tuple<C, x1, x2, x3, x4, ...> >
  NaiveBayesClassifier(const vector<vector<int>> &data,
                       int numberOfAttributes) {
    cout << "NaiveBayesClassifier()\n";
    // start training
    calculcateProbabilityPerClassAndAttribute(data, numberOfAttributes);
  };

  // predict class with attributes vector< attribute id>
  int predict(vector<int> attributes) {
    int maxProbabilityClassId = -1;
    double maxProbability = 0;
    for (const auto &[currentClassId, currentClassProbability] :
         classToProbabilityMap) {
      // p(C|x) = p(C)*p(x1|C)*p(x2|C)*…
      double pCx = currentClassProbability;
      for (int attributeId = 0; attributeId < attributes.size();
           attributeId++) {
        pCx *= classToAttributeProbabilityMap[currentClassId][attributeId]
                                             [attributes[attributeId]];
      }

      if (pCx > maxProbability) {
        maxProbability = pCx;
        maxProbabilityClassId = currentClassId;
      }
    }

    cout << "Predict Class : " << classIdToStringMap.at(maxProbabilityClassId)
         << " P(C|x1,x2,...,xN) = " << maxProbability << endl;

    return maxProbabilityClassId;
  }
};

pair<InputEntries, NumberOfAttributes> generateInputDataForNaiveBayesClassifier(
    istream &is) {
  InputEntries data;

  string line;
  while (getline(is, line)) {
    vector<string> strs;
    boost::algorithm::split(strs, line, boost::is_any_of(","));
    vector<int> dataEntry;

    if (strs.size() != 17) {
      throw "Something is wrong with the input data...";
    }

    if (strs[0] == "republican") {
      dataEntry.push_back(1);  // id of republican
    } else if (strs[0] == "democrat") {
      dataEntry.push_back(0);  // id of democrat
    } else {
      throw "Invalid class!";
    }

    for (int i = 1; i < strs.size(); i++) {
      if (strs[i] == "y") {
        dataEntry.push_back(0);
      } else if (strs[i] == "n") {
        dataEntry.push_back(1);
      } else if (strs[i] == "?") {
        dataEntry.push_back(2);
      } else {
        throw "Invalid value for attribute!";
      }
    }

    data.push_back(dataEntry);
  }
  return {data, 16};  // number of attributes are 16 - hardcoded...
}

vector<InputEntries> splitIntoSubsets(InputEntries data, int numberOfSubsets) {
  cout << "Input data size: [" << data.size() << "]\n";
  cout << "Number of subsets: [" << numberOfSubsets << "]\n";
  auto rng = std::default_random_engine{};
  std::shuffle(std::begin(data), std::end(data), rng);

  int numberOfElementsInSubset =
      ceil(static_cast<double>(data.size()) / numberOfSubsets);
  cout << "numberOfElementsInSubset = [" << numberOfElementsInSubset << "]\n";

  int numberOfElementsInLastSubset = data.size() - (numberOfElementsInSubset * (numberOfSubsets - 1));
  cout << "Number of elements in last subset should be equal to [" << numberOfElementsInLastSubset
       << "]\n";

  vector<InputEntries> result;

  // fill all but the last subset
  for (int chunk = 0; chunk < numberOfSubsets - 1; chunk++) {
    cout << "Filling subset number " << (chunk + 1) << endl;
    int startIndex = chunk * numberOfElementsInSubset;
    int endIndex = startIndex + numberOfElementsInSubset - 1;
    InputEntries inputEntries;
    for (int i = startIndex; i <= endIndex; i++) {
      inputEntries.push_back(data[i]);
    }
    result.push_back(inputEntries);
  }

  // fill last subset
  const int startIndex = (numberOfSubsets - 1) * numberOfElementsInSubset;
  const int endIndex = data.size() - 1;
  InputEntries inputEntries;
  for (int i = startIndex; i <= endIndex; i++) {
    inputEntries.push_back(data[i]);
  }
  result.push_back(inputEntries);
  cout << "Number of elements in last subset is equal to: [" << inputEntries.size() << "]\n";

  return result;
}

}  // namespace naivebayes