#include <iostream>
#include "Node/node.hpp"
using namespace std;

#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

class Suffix_tree {
private:
	string line;
	Node* current_node = nullptr;
	int current_edge = -1;
	int current_length = 0;
	int remain = 0;
	int suffix_end = -1;
	Node* last_node = nullptr;

	// �������� ����
	void delete_node(Node* node);

	// ���������� ������
	void update_tree(size_t index);

	// ���������� ����� ��������
	int suffix_length(Node* node) const;

public:
	Node* root;

	// ����� ������ � ������
	int find(string prompt);

	// ���������� ����������� ������
	void build(string text);

	// ����� ����������� ������
	void print(Node* start, int level);
};
#endif