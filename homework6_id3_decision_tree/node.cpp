#include "node.h"

#include "utils.h"

namespace id3 {

Node::Node(const Entries& dataEntries) {
  if (dataEntries.isEmpty()) {
    throw EmptyEntriesException("Trying to create a node without any entries!");
  } else if (dataEntries.areAllEntriesWithSameClass()) {
    Class cl = *dataEntries.getClasses().begin();
    optClass = make_optional(cl);
    m_bIsLeaf = true;
  }

  entries = dataEntries;
}

bool Node::isLeaf() const { return m_bIsLeaf; }

optional<AttributeId> Node::getAttribute() { return optAttributeId; }

void Node::setAttribute(optional<AttributeId> attributeId) {
  if (isLeaf()) {
    throw "Calling setAttribute() on a node which is marked to be a leaf!";
  }
  optAttributeId = attributeId;
}

optional<Class> Node::getClass() { return optClass; }

void Node::setClass(optional<Class> cl) {
  if (!isLeaf()) {
    throw "Calling setClass() on a node which is marked not to be a leaf!";
  }
  optClass = cl;
}

}  // namespace id3
