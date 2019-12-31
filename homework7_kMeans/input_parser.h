#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <iostream>
#include <vector>

namespace k_means {

using namespace std;

struct Point {
  double x{0}, y{0};
};

istream& operator>>(istream& is, Point& point) {
  return is >> point.x >> point.y;
}

namespace input_parse {

vector<Point> parse(istream& is) {
  vector<Point> result;
  Point p;
  while (is >> p) {
    result.push_back(p);
  }
  return result;
}

}  // namespace input_parse

}  // namespace k_means

#endif