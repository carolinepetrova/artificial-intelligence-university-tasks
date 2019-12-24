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

  naivebayes::NaiveBayesClassifier classifier{inputData, numberOfAttributes};

  auto subsets = naivebayes::splitIntoSubsets(inputData, 10);

  return 0;
}