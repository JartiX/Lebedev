#include <iostream>
#include "Node/node.hpp"
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

class Suffix_tree {
private:
	string line;
	Node* root = new Node(-1, nullptr, nullptr, -1);

	Node* current_node = nullptr;
	int current_edge = -1;
	int current_length = 0;
	int remain = 0;
	int suffix_end = -1;
	Node* last_node = nullptr;

	// Поиск узла
	Node* find_node(string substring);

	// Обновление дерева
	void update_tree(size_t index);

	// Вычисление длины суффикса
	int suffix_length(Node* node) const;

	// Собрать все суффиксы из узлов с использованием рекурсии
	void collect_suffixes(Node* node, vector<string>& suffixes) const;

	// Подсчет листовых узлов
	int cnt_leaf_nodes(Node* node);

public:
	// Получить корень дерева
	Node* Get_root();

	// Конструкторы
	Suffix_tree() {};
	Suffix_tree(string text);

	// Поиск строки в тексте
	int find(string prompt);

	// Количество вхождений строки
	int count_substring_entry(string substring);

	// Построение суффиксного дерева
	void build(string text);

	// Вывод суффиксного дерева
	void print(Node* start, int level);

	// Получение всех суффиксов
	vector<string> get_all_suffixes() const;

	// Проверка наличия подстроки в дереве
	bool is_contain(const string& substring);

	double operator ==(Suffix_tree& tree) const;
	friend istream& operator>>(istream& in, Suffix_tree& tree);
};
#endif