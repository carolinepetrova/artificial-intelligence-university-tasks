#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cmath>
#include <exception>
#include <vector>

using namespace std;

namespace id3 {

class InvalidSumOfProbabilitiesException : public std::exception {
 public:
  virtual const char* what() const noexcept override {
    return "Sum of all probabilites is not 1!";
  }
};

/**
 * @param probabilities - P(class 0) = probabilites[0], P(class 1) =
 * probabilities[1] and so on...
 *
 * The sum of the vector should be 1
 *
 * For example, if we have 3 shapes for an apple, and shape 0 has probability of
 * 0.5, then probabilites[0] = 0.5 The other 2 could be probabilites[1] = 0.3
 * and probabilites[2] = 0.2
 *
 * @throw InvalidVectorOfProbabilitiesException if the sum of the probabilities
 * is not 1
 * @return the entropy
 */
double calculateEntropy(const vector<double>& probabilities) {
  double sumOfProbabilites = 0;
  for (auto probability : probabilities) {
    sumOfProbabilites += probability;
  }

  if (sumOfProbabilites != 1) {
    throw InvalidSumOfProbabilitiesException();
  }

  double entropy = 0;
  for (auto probability : probabilities) {
    entropy -= probability * log2(probability);
  }
  return entropy;
}

}  // namespace id3

#endif