#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

namespace k_means {

struct Point {
  double x{0}, y{0};
};

using Centroid = Point;
using Centroids = vector<Centroid>;
using DataFrame = vector<Point>;
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

Centroids k_means(int k, const DataFrame& inputPoints,
                  int maxNumberOfIterations = 99999) {
  // Create k centroids
  Centroids centroids{k};

  // Initialize all the k centroids randomly
  for (auto& centroid : centroids) {
    centroid.x = util::generateRandomInteger(0, inputPoints.size());
    centroid.y = util::generateRandomInteger(0, inputPoints.size());
  }

  // Assign to each point in the input dataframe a centroid (thus mapping each
  // point index to a centroid)
  using PointIndexInDataFrame = int;
  unordered_map<PointIndexInDataFrame, Centroid> mapPointIndexToCentroid;

  for (int iteration = 0; iteration < maxNumberOfIterations; iteration++) {
    for (int pointIndex = 0; pointIndex < inputPoints.size(); ++pointIndex) {
      mapPointIndexToCentroid[pointIndex] =
          findClosestCentroidForAPoint(inputPoints[pointIndex], centroids);
    }
  }

  return centroids;
}

Centroid findClosestCentroidForAPoint(const Point& point,
                                      const Centroids& centroids) {
  if (centroids.empty()) {
    throw "No centroids!";
  }

  double minDistance = numeric_limits<double>::max();
  Centroid closestCentroid = centroids[0];
  for (const Centroid& centroid : centroids) {
    double distanceToCentroid = util::distance(point, centroid);
    if (distanceToCentroid < minDistance) {
      minDistance = distanceToCentroid;
      closestCentroid = centroid;
    }
  }
  return closestCentroid;
}

};  // namespace k_means

int main() {}