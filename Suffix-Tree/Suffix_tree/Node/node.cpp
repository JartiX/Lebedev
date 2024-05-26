#include "node.hpp"
using namespace std;


node::node(int left, int* right, node* suffix_link, int suffix_index) {
    this->left = left;
    this->right = right;
    this->suffix_link = suffix_link;
    this->suffix_index = suffix_index;
}