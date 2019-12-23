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

using Probability = double;
using AttributeId = int;
using Count = int;
using AttributeValue = int;

class NaiveBayesClassifier {
private:
  // <class id, class probability>; <C,P(C)>
  unordered_map<Class, Probability> classToProbabilityMap;

  // <class id, <attribute id, probability>>; <C, <x, P(x|C)>>
  unordered_map<Class, unordered_map<AttributeId, Probability>>
      classToAttributeProbabilityMap;

private:
  void countAllClassesAndAttributes(
      const vector<vector<int>> &data, int numberOfAttributes,
      unordered_map<Class, Count> &classToCountMap,
      unordered_map<Class, unordered_map<AttributeValue, Count>>
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

    for (auto &[currentClassId, attributeToProbabilityMap] :
         classToAttributeProbabilityMap) {
      cout << " - - - Class " << currentClassId << " - - - " << endl;
      for (auto &[attributeId, probability] : attributeToProbabilityMap) {
        probability =
            static_cast<double>(
                classToAttributeValueCountMap[currentClassId][attributeId]) /
            classToCountMap[currentClassId];
        cout << "Attribute P(x =" << attributeId << "|C ="
             << currentClassId // TODO: attributeIdToStringMap[attributeId]
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
        pCx *= classToAttributeProbabilityMap[currentClassId][attributes[i]];
      }

      if (pCx > maxProbability) {
        maxProbability = pCx;
        maxProbabilityClassId = currentClassId;
      }
    }
    cout << "Predict Class : "
         << maxProbabilityClassId // TODO:
                                  // classIdToStringMap[maxProbabilityClassId]
         << " P(C | x) = " << maxProbability << endl;
    return maxProbabilityClassId;
  }
};

using NumberOfAttributes = int;

// TODO:
pair<vector<vector<int>>, NumberOfAttributes>
generateInputDataForNaiveBayesClassifier(string inputFile) {}

int main() {
  cout << "TEST\n";
  return 0;
}