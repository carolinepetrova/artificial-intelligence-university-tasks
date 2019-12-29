#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <variant>

#include "entries.h"
#include "utils.h"

namespace id3 {

using namespace std;

class Node {
 private:
  /**
   * The data for the id3 algorithm on each tree node; if
   * the node is leaf, the entries will be 0
   */
  Entries m_Entries;

  /**
   * ID3 Decision tree:
   * If the node is leaf, it will contain class (the decision)
   * If the node is not leaf, it will containt an attribute
   */
  variant<AttributeId, Class> m_value;

  const bool m_bIsLeaf;

  /**
   * Map all attribute values to child nodes
   *
   * If the node is leaf then it will not contain any child nodes, and the map
   * will be empty
   */
  unordered_map<AttributeValue, Node*> m_mapChildren;

 public:
  explicit Node(const Entries& entries, AttributeId attributeId);
  explicit Node(const Entries& entries, Class cl);

  bool isLeaf() const;

  variant<AttributeId, Class> getValue() const;
};

}  // namespace id3

#endif