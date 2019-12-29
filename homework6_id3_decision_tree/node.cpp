#include "node.h"

#include <assert.h>

#include "unistd.h"
#include "utils.h"

namespace id3 {

Node::Node(const Entries& entries) : m_bIsLeaf{false} {
  cout << "Node(entries) BEGIN" << endl;
  if (entries.isEmpty()) {
    throw EmptyEntriesException("Trying to create a node without any entries!");
  }

  m_Entries = entries;
  m_value = entries.getAttributeWithHighestInformationGain();

  cout << "Node() Entries: \n" << entries << endl;
  cout << "Node() Attribute with highest information gain is ["
       << get<AttributeId>(m_value) << "]\n";
  cout << "Node(entries) END" << endl;
}

Node::Node(Class cl) : m_bIsLeaf{true}, m_value{cl} {
  cout << "Node(class) BEGIN" << endl;
  cout << "Node(class) END" << endl;
}

bool Node::isLeaf() const { return m_bIsLeaf; }

variant<AttributeId, Class> Node::getValue() const { return m_value; }

void Node::generateChildren() {
  if (isLeaf()) {
    throw "generateChildren() called on a leaf node!";
  }

  const auto currentAttributeId = std::get<AttributeId>(m_value);
  cout << "generateChildren() currentAttributeId = " << currentAttributeId
       << endl;

  for (const auto& currentAttributeValue :
       m_Entries.getAllPossibleAttributeValues(currentAttributeId)) {
    cout << "generateChildren() m_Entries:\n" << m_Entries << endl;
    auto subset =
        generateSubset(m_Entries, currentAttributeId, currentAttributeValue);
    cout << "generateChildren() subset:\n" << subset << endl;

    if (subset.isEmpty()) {
      cout << "Inserting leaf 1...\n";
      cout << "currentAttributeValue = [" << currentAttributeValue << "]\n";

      // insert leaf node with decision
      m_mapChildren.insert({currentAttributeValue,
                            make_shared<Node>(m_Entries.getMostCommonClass())});
      assert(m_mapChildren[currentAttributeValue]->isLeaf());
    } else if (subset.areAllEntriesWithSameClass()) {
      cout << "Inserting leaf 2...\n";
      cout << "currentAttributeValue = [" << currentAttributeValue << "]\n";

      // insert leaf node with decision
      m_mapChildren.insert({currentAttributeValue,
                            make_shared<Node>(*subset.getClasses().begin())});
      assert(m_mapChildren[currentAttributeValue]->isLeaf());
    } else {
      cout << "Inserting non-leaf...\n";
      cout << "currentAttributeValue = [" << currentAttributeValue << "]\n";

      // insert non-leaf node for further ID3 algorithm work
      m_mapChildren.insert({currentAttributeValue, make_shared<Node>(subset)});
      assert(!m_mapChildren[currentAttributeValue]->isLeaf());
    }
  }
}

vector<shared_ptr<Node>> Node::getChildren() {
  vector<shared_ptr<Node>> result;
  for (const auto& [attributeValue, child] : m_mapChildren) {
    result.push_back(child);
  }
  return result;
}

unordered_map<AttributeValue, shared_ptr<Node>> Node::getChildrenMap() {
  return m_mapChildren;
}

Entries Node::getEntries() const { return m_Entries; }

void Node::printAttributeValuesToChildren(std::ostream& os) const {
  for (const auto& [value, tmp] : m_mapChildren) {
    os << "attribute value: " << value << endl;
  }
}

}  // namespace id3
