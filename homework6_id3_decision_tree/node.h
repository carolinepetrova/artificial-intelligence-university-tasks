#ifndef NODE_H
#define NODE_H

#include <optional>
#include <unordered_map>

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
  Entries entries;

  optional<AttributeId> optAttributeId;
  optional<Class> optClass;
  bool m_bIsLeaf;

  /**
   *  @brief map all attribute values to child nodes
   *
   * If the node is leaf then it will not contain any child nodes, and the map
   * will be empty
   */
  unordered_map<AttributeValue, Node*> children;

 public:
  Node(const Entries& dataEntries);

  bool isLeaf() const;

  /**
   * If the node is leaf, then it will not contain attribute, because it will
   * contain a class, which is the decision itself
   */
  optional<AttributeId> getAttribute();
  void setAttribute(optional<AttributeId> attributeId);

  /**
   * If then node is leaf, then it will contain a class (the decision itself)
   */
  optional<Class> getClass();
  void setClass(optional<Class> cl);
};

}  // namespace id3

#endif