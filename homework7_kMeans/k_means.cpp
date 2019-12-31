#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

namespace k_means {

struct Point {
  double x{0}, y{0};
};

namespace util {
double square(double value) { return value * value; }

double distance(Point p1, Point p2) {
  return sqrt(square(p1.x - p2.x) + square(p1.y - p2.y));
}

/**
 * @brief generate random integer between start and end, including both start
 * and end
 */
int generateRandomInteger(int start, int end) {
  static default_random_engine generator;
  uniform_int_distribution<int> distribution{start, end};
  return distribution(generator);
}

}  // namespace util

using Centroids = vector<Point>;
using DataFrame = vector<Point>;

Centroids k_means(int k, const DataFrame& input,
                  int maxNumberOfIterations = 99999) {
  return {};
}

};  // namespace k_means

int main() {}