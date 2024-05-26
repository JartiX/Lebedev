#include <iostream>
#include "Node/node.hpp"
using namespace std;

#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

struct suffix_tree {
private:
    string line;
    node* active_node = nullptr;
    int active_edge = -1;
    int active_length = 0;
    int remain = 0;
    int suffix_end = -1;

    node* last_created = nullptr;
    void del(node* node);
    void update_tree(int index);
    int suffix_length(node* node) const;

public:
    node* root;

    void build(string data);
    void print(node* start, int lvl);
    int find(string text);
};
#endif