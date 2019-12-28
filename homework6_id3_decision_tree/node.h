#ifndef NODE_H
#define NODE_H

#include <optional>
#include <unordered_map>

#include "utils.h"

namespace id3 {

using namespace std;

class Node {
 private:
  optional<AttributeId> optAttributeId;
  optional<Class> optClass;

  /**
   *  @brief map all attribute values to child nodes
   *
   * If the node is leaf then it will not contain any child nodes, and the map
   * will be empty
   */
  unordered_map<AttributeValue, Node*> children;

 public:
  bool isLeaf() const;

  /**
   * If the node is leaf, then it will not contain attribute
   */
  optional<AttributeId> getAttribute();

  /**
   * If then node is leaf, then it will contain a class (the decision itself)
   */
  optional<Class> getClass();
};

}  // namespace id3

#endif