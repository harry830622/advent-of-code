#include <boost/tokenizer.hpp>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Tree {
 public:
  class Node {
   public:
    Node(const std::string& name)
        : name_(name), parent_id_(-1), child_ids_(), depth_(0) {}

    std::string name_;
    int parent_id_;
    std::vector<int> child_ids_;
    int depth_;
    int dist_from_you_;
  };

  Tree() : root_id_(-1), nodes_(), node_id_by_name_() {
    root_id_ = AddNode(Node("COM"));
  }

  int AddNode(const Node& node) {
    int new_node_id = nodes_.size();
    nodes_.push_back(node);
    node_id_by_name_.insert({node.name_, new_node_id});
    return new_node_id;
  }

  int root_id_;
  std::vector<Node> nodes_;
  std::unordered_map<std::string, int> node_id_by_name_;
};

int main() {
  Tree orbit_map_tree;
  int you_id = -1;
  int san_id = -1;
  std::string str;
  boost::char_separator<char> sep(")");
  while (std::cin >> str) {
    boost::tokenizer<boost::char_separator<char>> tokenizer(str, sep);
    std::vector<std::string> tokens(tokenizer.begin(), tokenizer.end());
    const std::string orbited_object_name(tokens[0]);
    const std::string object_name(tokens[1]);
    if (orbit_map_tree.node_id_by_name_.find(orbited_object_name) ==
        orbit_map_tree.node_id_by_name_.end()) {
      orbit_map_tree.AddNode(Tree::Node(orbited_object_name));
    }
    if (orbit_map_tree.node_id_by_name_.find(object_name) ==
        orbit_map_tree.node_id_by_name_.end()) {
      orbit_map_tree.AddNode(Tree::Node(object_name));
    }
    const int orbited_object_node_id =
        orbit_map_tree.node_id_by_name_.at(orbited_object_name);
    const int object_node_id = orbit_map_tree.node_id_by_name_.at(object_name);
    orbit_map_tree.nodes_.at(object_node_id).parent_id_ =
        orbited_object_node_id;
    orbit_map_tree.nodes_.at(orbited_object_node_id)
        .child_ids_.push_back(object_node_id);
    if (you_id == -1) {
      if (orbited_object_name == "YOU") {
        you_id = orbited_object_node_id;
      } else if (object_name == "YOU") {
        you_id = object_node_id;
      }
    }
    if (san_id == -1) {
      if (orbited_object_name == "SAN") {
        san_id = orbited_object_node_id;
      } else if (object_name == "SAN") {
        san_id = object_node_id;
      }
    }
  }
  int curr_id = -1;
  std::queue<int> bfs_q;
  bfs_q.push(orbit_map_tree.root_id_);
  while (!bfs_q.empty()) {
    curr_id = bfs_q.front();
    bfs_q.pop();
    const Tree::Node& curr_node = orbit_map_tree.nodes_.at(curr_id);
    for (int child_id : curr_node.child_ids_) {
      Tree::Node& child = orbit_map_tree.nodes_.at(child_id);
      child.depth_ = curr_node.depth_ + 1;
      bfs_q.push(child_id);
    }
  }
  int total_orbits = 0;
  for (const Tree::Node& node : orbit_map_tree.nodes_) {
    total_orbits += node.depth_;
  }
  std::cout << total_orbits << std::endl;
  std::unordered_set<int> path_ids;
  int curr_dist = 0;
  curr_id = you_id;
  while (curr_id != -1) {
    path_ids.insert(curr_id);
    Tree::Node& curr_node = orbit_map_tree.nodes_.at(curr_id);
    curr_node.dist_from_you_ = curr_dist;
    ++curr_dist;
    curr_id = curr_node.parent_id_;
  }
  int dist_from_san = 0;
  curr_id = san_id;
  while (curr_id != -1) {
    Tree::Node& curr_node = orbit_map_tree.nodes_.at(curr_id);
    if (path_ids.find(curr_id) != path_ids.end()) {
      std::cout << dist_from_san + curr_node.dist_from_you_ - 2 << std::endl;
      break;
    }
    ++dist_from_san;
    curr_id = curr_node.parent_id_;
  }

  return 0;
}
