#include "id3.h"

#include <assert.h>

#include <iostream>

using namespace std;

namespace id3 {

unique_ptr<Node> ID3Algorithm::generateDecisionTree(const Entries& inputData) {
  cout << "generateDecisionTree()\n";
  if (inputData.isEmpty()) {
    throw "Calling generateDecisionTree() on an empty dataset.";
  }

  if (inputData.areAllEntriesWithSameClass()) {
    cout << "Returning leaf node. All entries are with the same class: ["
         << *inputData.getClasses().begin() << "]\n";
    return make_unique<Node>(*inputData.getClasses().begin());
  }

  assert(false);  // just test it works

  AttributeId attributeWithHighestInformationGain =
      inputData.getAttributeWithHighestInformationGain();

  cout << "Attribute with highest information gain is ["
       << attributeWithHighestInformationGain << "]\n";

  auto rootNode =
      make_unique<Node>(inputData, attributeWithHighestInformationGain);
  assert(rootNode->isLeaf());

  rootNode->generateChildren();

  for (const auto& child : rootNode->getChildren()) {
    generateDecisionTree(child->getEntries());
  }

  return rootNode;
}

}  // namespace id3
