#ifndef ID3_H
#define ID3_H

#include <memory>

#include "entries.h"
#include "node.h"

namespace id3 {

using namespace std;

class ID3Algorithm {
 private:
  void generateDecisionTreeHelper(shared_ptr<Node> rootNode);
 public:
  shared_ptr<Node> generateDecisionTree(const Entries& inputData);
};

}  // namespace id3

#endif