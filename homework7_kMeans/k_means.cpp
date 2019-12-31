#include <algorithm>
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

bool operator==(const Point& lhs, const Point& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

ostream& operator<<(ostream& os, const Point& p) {
  return os << "(" << p.x << ", " << p.y << ")";
}

bool operator!=(const Point& lhs, const Point& rhs) { return !(lhs == rhs); }

using Centroid = Point;
using Centroids = vector<Centroid>;
using DataFrame = vector<Point>;
using Means = vector<Point>;
using PointIndexInDataFrame = int;
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

void initializeCentroidsRandomly(Centroids& centroids, long long from = 0,
                                 long long to = 999999);

vector<Point> findPointsBelongingToCentroid(
    const Centroid& centroid, const DataFrame& inputPoints,
    const unordered_map<PointIndexInDataFrame, Centroid>&
        mapPointIndexToCentroid);

Centroid findClosestCentroidForAPoint(const Point& point,
                                      const Centroids& centroids);

/**
 * Return a set of means for the given dataframe,
 * generated by the k-means algorithm
 */
Means k_means(long unsigned k, const DataFrame& inputPoints,
              int numberOfIterations = 100'000, ostream& logOs = cout) {
  logOs << "k_means() algorithm begins. Number of iterations = "
        << numberOfIterations << "\n";

  logOs << "Input points:\n";
  for (const Point& point : inputPoints) {
    logOs << point << " ";
  }
  logOs << endl;

  logOs << "Creating k centroids and initializing them randomly.\n";
  // Create k centroids
  Centroids centroids{k};
  initializeCentroidsRandomly(centroids, 0, inputPoints.size());

  // Assign to each point in the input dataframe a centroid (thus mapping each
  // point index to a centroid)
  unordered_map<PointIndexInDataFrame, Centroid> mapPointIndexToCentroid;

  logOs << "Begin of " << numberOfIterations << " iterations.\n";
  for (int iteration = 0; iteration < numberOfIterations; iteration++) {
    // Assign to each point a centroid
    for (int pointIndex = 0; pointIndex < inputPoints.size(); ++pointIndex) {
      mapPointIndexToCentroid[pointIndex] =
          findClosestCentroidForAPoint(inputPoints[pointIndex], centroids);
    }

    // Find the mean point for each centroid and assign to the centroid that
    // mean point
    for (auto& centroid : centroids) {
      Point meanPoint{0, 0};
      const auto pointsBelongingToCentroid = findPointsBelongingToCentroid(
          centroid, inputPoints, mapPointIndexToCentroid);

      for (const auto& point : pointsBelongingToCentroid) {
        meanPoint.x += point.x;
        meanPoint.y += point.y;
      }

      meanPoint.x =
          meanPoint.x / max<size_t>(pointsBelongingToCentroid.size(), 1);
      meanPoint.y =
          meanPoint.y / max<size_t>(pointsBelongingToCentroid.size(), 1);

      centroid = meanPoint;
    }
  }
  logOs << "End of " << numberOfIterations << " iterations.\n";

  return centroids;
}

vector<Point> findPointsBelongingToCentroid(
    const Centroid& centroid, const DataFrame& inputPoints,
    const unordered_map<PointIndexInDataFrame, Centroid>&
        mapPointIndexToCentroid) {
  vector<Point> result;
  for (int pointIndex = 0; pointIndex < inputPoints.size(); ++pointIndex) {
    if (mapPointIndexToCentroid.at(pointIndex) == centroid) {
      result.push_back(inputPoints[pointIndex]);
    }
  }
  return result;
}

void initializeCentroidsRandomly(Centroids& centroids, long long from,
                                 long long to) {
  for (auto& centroid : centroids) {
    centroid.x = util::generateRandomInteger(from, to);
    centroid.y = util::generateRandomInteger(from, to);
  }
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

void simpleTest(ostream& logOs = cout) {
  auto means = k_means::k_means(3, {{0, 0},
                                    {1, 1},
                                    {1000, 1000},
                                    {1001, 1001},
                                    {50000, 50000},
                                    {60000, 60000}});

  logOs << "Means generated by algorithm:\n";
  for (const auto& mean : means) {
    logOs << "(" << mean.x << ", " << mean.y << ")\n";
  }
}

int main() { simpleTest(); }