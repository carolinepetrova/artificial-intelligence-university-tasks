#include "node.h"

#include "utils.h"

namespace id3 {

Node::Node(const Entries& entries, AttributeId attributeId) : m_bIsLeaf{false} {
  if (entries.isEmpty()) {
    throw EmptyEntriesException("Trying to create a node without any entries!");
  }

  m_Entries = entries;
  m_value = attributeId;
}

Node::Node(const Entries& entries, Class cl) : m_bIsLeaf{true} {
  if (entries.isEmpty()) {
    throw EmptyEntriesException("Trying to create a node without any entries!");
  }

  m_Entries = entries;
  m_value = cl;
}

bool Node::isLeaf() const { return m_bIsLeaf; }

variant<AttributeId, Class> Node::getValue() const { return m_value; }

}  // namespace id3
