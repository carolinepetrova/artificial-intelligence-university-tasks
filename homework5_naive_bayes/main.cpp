#include <fstream>

#include "naive_bayes.h"

int main() {
  std::string inputFile = "input_data/house-votes-84.data";
  ifstream is{inputFile};
  if (!is) {
    throw "Could not open input file!";
  }

  const auto& [inputData, numberOfAttributes] =
      naivebayes::generateInputDataForNaiveBayesClassifier(is);

  cout << "Splitting data into subsets...\n";
  auto subsets = naivebayes::splitIntoSubsets(inputData, 10);

  vector<double> accuracies;

  for (int testSubset = 0; testSubset <= 9; testSubset++) {
    // testSubset will be used for testing, all the other subsets will be used
    // for training
    cout << "\n--------------------- TEST SUBSET WILL BE " << testSubset
         << " ---------------------\n\n";

    // start constructing training set
    naivebayes::InputEntries trainingSet;
    for (int subset = 0; subset <= 9; subset++) {
      if (subset == testSubset)
        continue;  // do not add testSubset to trainingSet

      trainingSet.insert(trainingSet.end(), subsets[subset].begin(),
                         subsets[subset].end());
    }

    // ok, now we have a training set, let's train our model!
    naivebayes::NaiveBayesClassifier classifier{trainingSet,
                                                numberOfAttributes};

    // now that we've trained our model, let's use the testSubset for some
    // predictions...
    cout << "\n ------------ PREDICTIONS START ------------\n";
    int successfulPredictions = 0, totalPredictions = 0;
    for (const auto& entry : subsets[testSubset]) {
      string actualClass = naivebayes::classIdToStringMap.at(entry[0]);

      vector<int> attributes{entry.begin() + 1, entry.end()};
      string predictedClass = classifier.predict(attributes);

      cout << "Attributes: [";
      for (auto attributeValue : attributes) {
        cout << attributeValue << ",";
      }
      cout << "]; actual class: " << actualClass
           << "; predicted class: " << predictedClass << endl;

      totalPredictions++;
      if (actualClass == predictedClass) successfulPredictions++;
    }

    cout << "Results:\n";
    cout << "Successful predictions: " << successfulPredictions << endl;
    cout << "Total predictions: " << totalPredictions << endl;
    double accuracy =
        (static_cast<double>(successfulPredictions) / totalPredictions);
    accuracies.push_back(accuracy);
    cout << "Accuracy: " << accuracy << endl;
    cout << "--------------------- TEST FINISH FOR SUBSET " << testSubset
         << " ---------------------\n\n";
  }

  auto accuraciesSum = accumulate(accuracies.begin(), accuracies.end(), 0.0);

  cout << "Mean of all accuracies: " << (accuraciesSum / accuracies.size())
       << endl;

  return 0;
}