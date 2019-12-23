#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// What the classifier has to calculate is:
// input -> x1, ..., xN (attributes)
// output -> the most probable Ck for the input attributes - Ck with max
// P(Ck|x1,...,xN)

// Theory: The Ck with the largest P(Ck|x1,...,xN) is the Ck with the largest
// P(Ck)*P(x1|Ck)*...*P(xN|Ck) Hence the unordered_map structures in the class
// NaiveBayesClassifier

// enum class Class { REPUBLICAN, DEMOCRAT };
using Class = int;

// enum class AttributeValue {
//   YES,
//   NO,
//   INDETERMINATE,
// };

// TODO: Map classes, attributes and attributes' values to int

using ClassId = int;
using Probability = double;
using AttributeId = int;
using Count = int;
using AttributeValue = int;
using NumberOfAttributes = int;

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
private:
  // <class id, class probability>; <C,P(C)>
  unordered_map<ClassId, Probability> classToProbabilityMap;

  // <class id, <attribute value, probability>>; <C, <x=attributevalue, P(x=attributevalue|C)>>
  unordered_map<ClassId, unordered_map<AttributeValue, Probability>>
      classToAttributeValueProbabilityMap;

private:
  void countAllClassesAndAttributes(
      const vector<vector<int>> &data, int numberOfAttributes,
      unordered_map<ClassId, Count> &classToCountMap,
      unordered_map<ClassId, unordered_map<AttributeValue, Count>>
          &classToAttributeValueCountMap) {
    for (auto entry : data) {
      const int currentClass = entry[0];
      if (classToCountMap.find(currentClass) == classToCountMap.end()) {
        classToCountMap[currentClass] = 1;
        classToAttributeValueCountMap[currentClass] = {};
      } else {
        classToCountMap[currentClass] += 1;
      }

      for (int attributeId = 1; attributeId <= numberOfAttributes;
           attributeId++) {
        const int attributeValue = entry[attributeId];
        auto &currentClassAttributeToCountMap =
            classToAttributeValueCountMap[currentClass];
        if (currentClassAttributeToCountMap.find(attributeValue) ==
            currentClassAttributeToCountMap.end()) {
          currentClassAttributeToCountMap[attributeValue] = 1;
        } else {
          currentClassAttributeToCountMap[attributeValue] += 1;
        }
      }
    }
  }

  void
  calculcateProbabilityPerClassAndAttribute(const vector<vector<int>> &data,
                                            int numberOfAttributes) {

    // count classes <C, Number of instances with class C>
    unordered_map<Class, Count> classToCountMap;

    // count attributes per class <C, <AttributeValue, Count>>
    // for example:
    // <class Apple -> <color attribute {Red -> 8}, {Green -> 23}, shape
    // attribute {Oval -> 69}, {Heart -> 15}> >
    unordered_map<Class, unordered_map<AttributeValue, Count>>
        classToAttributeValueCountMap;

    countAllClassesAndAttributes(data, numberOfAttributes, classToCountMap,
                                 classToAttributeValueCountMap);

    for (auto &[currentClassId, attributeValueToProbabilityMap] :
         classToAttributeValueProbabilityMap) {
      cout << " - - - Class " << currentClassId << " - - - " << endl;
      for (auto &[attributeValue, probability] : attributeValueToProbabilityMap) {
        probability =
            static_cast<double>(
                classToAttributeValueCountMap[currentClassId][attributeValue]) /
            classToCountMap[currentClassId];
        cout << "Attribute " << attributeIdToStringMap<< " P(x =" << attributeValueToStringMap.at(attributeValue)
             << "|C =" << classIdToStringMap.at(currentClassId)
             << ") = " << probability << endl;
      }

      classToProbabilityMap[currentClassId] =
          static_cast<double>(classToCountMap[currentClassId]) / data.size();
      cout << "Class P(C ="
           << currentClassId // TODO: classIdToStringMap[currentClassId]
           << ") = " << classToProbabilityMap[currentClassId] << endl;
    }
  }

public:
  // input: vector< tuple<C, x1, x2, x3, x4, ...> >
  NaiveBayesClassifier(const vector<vector<int>> &data,
                       int numberOfAttributes) {
    // start training
    calculcateProbabilityPerClassAndAttribute(data, numberOfAttributes);
  };

  // predict class with attributes vector< attribute id>
  int predict(vector<int> attributes) {
    int maxProbabilityClassId = -1;
    double maxProbability = 0;
    for (const auto &[currentClassId, probabilityOfCurrentClass] :
         classToProbabilityMap) {
      // p(C|x) = p(C)*p(x1|C)*p(x2|C)*…
      double pCx = probabilityOfCurrentClass;
      for (int i = 0; i < attributes.size(); i++) {
        pCx *= classToAttributeValueProbabilityMap[currentClassId][attributes[i]];
      }

      if (pCx > maxProbability) {
        maxProbability = pCx;
        maxProbabilityClassId = currentClassId;
      }
    }
    cout << "Predict Class : " << classIdToStringMap.at(maxProbabilityClassId)
         << " P(C | x) = " << maxProbability << endl;
    return maxProbabilityClassId;
  }
};

// TODO:
pair<vector<vector<int>>, NumberOfAttributes>
generateInputDataForNaiveBayesClassifier(string inputFile) {}

int main() {
  cout << "TEST\n";
  return 0;
}