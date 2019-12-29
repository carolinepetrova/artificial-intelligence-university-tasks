#ifndef ID3_H
#define ID3_H

#include <memory>

#include "entries.h"
#include "node.h"

namespace id3 {

using namespace std;

class ID3Algorithm {
 private:
 public:
  unique_ptr<Node> generateDecisionTree(const Entries& inputData);
};

}  // namespace id3

#endif