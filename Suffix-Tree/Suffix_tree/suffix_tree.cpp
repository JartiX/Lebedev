#include "suffix_tree.hpp"
using namespace std;

void Suffix_tree::delete_node(Node* node) {
	// ����������� �������� ����� ����
	for (pair<const char, Node*> i : node->childs) {
		delete_node(i.second);
	}

	// ���� ���� ����������, ������� � right
	if (node->suffix_index == -1) { delete node->right; }

	// ������� ��� ����
	delete node;
}

void Suffix_tree::update_tree(size_t index) {
	last_node = nullptr;
	remain++;
	suffix_end++;

	// ����� ����������� �� ��� ���, ���� ��� �������� �� ����� ����������
	while (remain > 0) {
		if (current_length == 0) {
			current_edge = index;
		}

		// ���� �������� ����, ������� � ������� �� ������� ����� 
		auto finded_child = current_node->childs.find(line[current_edge]);

		// ���� ����� ���� �� �������
		if (finded_child == current_node->childs.end()) {
			// ������� ����� ����
			Node* added_word = new Node(index, &suffix_end, root, index - remain + 1);

			// ��������� ���� ��������� � �������� ���� �������� ����
			current_node->childs[line[index]] = added_word;

			// ��������� ������ ����������� ���������� ����, ���� ��� ����
			if (last_node != nullptr) {
				last_node->suffix_link = current_node;
				last_node = nullptr;
			}
		}
		// ���� ����� �������� ����
		else {
			Node* finded_node = finded_child->second;

			// ���������� � ����
			if (current_length >= suffix_length(finded_node)) {
				current_node = finded_node;
				current_length -= suffix_length(finded_node);
				current_edge += suffix_length(finded_node);
				continue;
			}

			// ���������� �� �����
			// ���� ������ ������ � �������� �� ������� �����
			if (line[index] == line[finded_child->second->left + current_length]) {
				// ��������� ������ ����������� ����, ���� ����
				if (last_node != nullptr && current_node != root) {
					last_node->suffix_link = current_node;
				}
				current_length++;
				break;
			}

			// ���� ������ �� ������, �� ��������� �����
			Node* new_node = new Node(finded_node->left, new int(finded_node->left + current_length - 1), root, index - remain + 1);

			if (last_node != nullptr) {
				last_node->suffix_link = new_node;
			}

			// ��������� ������� ���� � ��� �������� ����
			current_node->childs[line[current_edge]] = new_node;
			finded_node->left += current_length;

			new_node->childs[line[index]] = new Node(index, &suffix_end, root, index - remain + 1);
			new_node->childs[line[finded_node->left]] = finded_node;
			last_node = new_node;
		}
		// ��������� ���������� ����� ��������� ��������
		remain--;

		if (current_length > 0 && current_node == root) {
			current_length--;
			current_edge++;
		}
		else if (current_node != root) {
			current_node = current_node->suffix_link;
		}
	}
}

int Suffix_tree::suffix_length(Node* node) const {
	if (node == root) return 0;

	return *node->right - node->left + 1;
}


int Suffix_tree::find(string prompt) {
	// ���� ������ ������ ��� ������, ������ 0
	if (prompt.empty()) {
		return 0;
	}

	// �������� ������ � �����
	Node* current_node = root;
	size_t depth = 0;
	int prompt_len = prompt.length();

	while (depth < prompt.length()) {
		auto finded_child = current_node->childs.find(prompt[depth]);

		// ���� ���� � ������ �������� ���, ������ -1
		if (finded_child == current_node->childs.end()) {
			return -1;
		}
		Node* finded_node = finded_child->second;
		int node_len = suffix_length(finded_node);

		// ��������� ������������ �������� � ��������� ����
		for (size_t i = 0; i < node_len; i++) {
			// ���� �������� ����� ������ prompt, ������ ������ ��������
			if (depth + i >= prompt_len) {
				return finded_node->suffix_index;
			}
			
			// ���� ������� �� �������, ������ -1
			if (prompt[depth + i] != line[finded_node->left + i]) {
				return -1;
			}
		}

		// ��������� � ���������� ����
		current_node = finded_node;
		depth += node_len;
	}
	return current_node->suffix_index;
}

void Suffix_tree::build(string text) {
	// ������� ������
	root = new Node(-1, nullptr, nullptr, -1);
	
	// ������� ������, ���� �� ��� ���
	if (!root->childs.empty()) { delete_node(root); }

	// ���������������� ����� � ������� ����
	line = text;
	current_node = root;

	// ���������� ������� ������ � ���������� ������
	for (size_t i = 0; line[i] != '\0'; i++) {
		update_tree(i);
	}

	// ������������ ����� ������
	update_tree(line.length());
}

void Suffix_tree::print(Node* start, int level) {
	// �������� �� ���� �������� ����� �������� ����
	for (pair<const char, Node*> mapa : start->childs) {
		// ���������� ������, ���� ��� ����� ������
		if (mapa.first == '\0') {
			continue;
		}

		// ������ ��� ����������� ������������� ������� ���� � ������
		for (int i = 0; i < level; i++) {
			cout << "->";
		}

		// ������� ��� ������� ����
		for (int i = mapa.second->left; i <= *(mapa.second->right); i++) {
			cout << line[i];
		}
		cout << endl;

		// ���� ������� ���� ����� �������� ����, �� ���������� �������� �������
		// ��� ������� ��������� ����, ��� ���� ���������� �������
		if (!(start->childs.empty())) {
			print(mapa.second, level + 1);
		}
	}
}