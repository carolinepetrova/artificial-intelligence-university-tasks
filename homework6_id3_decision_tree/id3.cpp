#include "id3.h"

#include <assert.h>

#include <iostream>
#include <variant>

#include "unistd.h"

using namespace std;

namespace id3 {

shared_ptr<Node> ID3Algorithm::generateDecisionTree(const Entries& inputData) {
  cout << "generateDecisionTree()\n";
  if (inputData.isEmpty()) {
    throw "Calling generateDecisionTree() on an empty dataset.";
  }

  if (inputData.areAllEntriesWithSameClass()) {
    cout << "Returning leaf node. All entries are with the same class: ["
         << *inputData.getClasses().begin() << "]\n";

    auto rootNode = make_shared<Node>(*inputData.getClasses().begin());
    assert(rootNode->isLeaf());
    return rootNode;
  }

  auto rootNode = make_shared<Node>(inputData);

  assert(!rootNode->isLeaf());

  generateDecisionTreeHelper(rootNode);

  return rootNode;
}

void ID3Algorithm::generateDecisionTreeHelper(shared_ptr<Node> rootNode) {
  auto attr = std::get<id3::AttributeId>(rootNode->getValue());
  cout << "generateDecisionTreeHelper() " << attr << endl;
  cout << "Before rootNode->generateChildren()\n";
  rootNode->generateChildren();
  cout << "After rootNode->generateChildren()\n";
  for (const auto& child : rootNode->getChildren()) {
    if (!child->isLeaf()) {
      cout << "child has value attr id: "
           << std::get<id3::AttributeId>(child->getValue())
           << " and size of entries: " << child->getEntries().getData().size()
           << endl;
      generateDecisionTreeHelper(child);
    }
  }
}

}  // namespace id3
