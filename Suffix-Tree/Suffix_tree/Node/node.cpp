#include "node.hpp"
using namespace std;


Node::Node(int left_, int* right_, Node* suffix_link_, int suffix_index_) {
	left = left_;
	right = right_;
	suffix_index = suffix_index_;
	suffix_link = suffix_link_;
}

void Node::delete_node() {
	// Рекурсивное удаление детей узла
	for (pair<const char, Node*> i : this->childs) {
		i.second->delete_node();
	}

	// Если узел внутренний, удаляем и right
	if (this->suffix_index == -1) { delete this->right; }

	// Удаляем сам узел
	delete this;
}