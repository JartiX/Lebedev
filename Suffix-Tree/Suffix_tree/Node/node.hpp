#include <unordered_map>
using namespace std;

#ifndef NODE_HPP
# define NODE_HPP

struct node {
    int left, *right, suffix_index;
    node* suffix_link;
    unordered_map<char, node*> childs;

    node(int left, int* right, node* suffix_link, int suffix_index);
};


#endif
