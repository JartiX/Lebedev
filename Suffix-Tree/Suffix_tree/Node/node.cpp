#include "node.hpp"
using namespace std;


Node::Node(int left_, int* right_, Node* suffix_link_, int suffix_index_) {
	left = left_;
	right = right_;
	suffix_index = suffix_index_;
	suffix_link = suffix_link_;
}