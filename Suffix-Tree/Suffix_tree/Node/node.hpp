#include <unordered_map>
using namespace std;

#ifndef NODE_HPP
# define NODE_HPP

struct Node {
	int left;
	int* right;
	size_t suffix_index;
	Node* suffix_link;
	unordered_map<char, Node*> childs;

	Node(int left_, int* right_, Node* suffix_link_, int suffix_index_);
};


#endif
