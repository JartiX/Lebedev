#include "suffix_tree.hpp"
using namespace std;

void Suffix_tree::delete_node(Node* node) {
	// Рекурсивное удаление детей узла
	for (pair<const char, Node*> i : node->childs) {
		delete_node(i.second);
	}

	// Если узел внутренний, удаляем и right
	if (node->suffix_index == -1) { delete node->right; }

	// Удаляем сам узел
	delete node;
}

void Suffix_tree::update_tree(size_t index) {
	last_node = nullptr;
	remain++;
	suffix_end++;

	// Будет выполняться до тех пор, пока все суффиксы не будут обработаны
	while (remain > 0) {
		if (current_length == 0) {
			current_edge = index;
		}

		// Ищем дочерний узел, начиная с символа на текущем ребре 
		auto finded_child = current_node->childs.find(line[current_edge]);

		// Если такой узел не нашелся
		if (finded_child == current_node->childs.end()) {
			// Создаем новый узел
			Node* added_word = new Node(index, &suffix_end, root, index - remain + 1);

			// Созданный узел добавляем в дочерние узлы текущего узла
			current_node->childs[line[index]] = added_word;

			// Обновляем ссылку предыдущего созданного узла, если она есть
			if (last_node != nullptr) {
				last_node->suffix_link = current_node;
				last_node = nullptr;
			}
		}
		// Если нашли дочерний узел
		else {
			Node* finded_node = finded_child->second;

			// Спускаемся к узлу
			if (current_length >= suffix_length(finded_node)) {
				current_node = finded_node;
				current_length -= suffix_length(finded_node);
				current_edge += suffix_length(finded_node);
				continue;
			}

			// Спускаемся по ребру
			// Если символ совпал с символом на текущей длине
			if (line[index] == line[finded_child->second->left + current_length]) {
				// Обновляем ссылку предыдущего узла, если есть
				if (last_node != nullptr && current_node != root) {
					last_node->suffix_link = current_node;
				}
				current_length++;
				break;
			}

			// Если символ не совпал, то разделяем ребро
			Node* new_node = new Node(finded_node->left, new int(finded_node->left + current_length - 1), root, index - remain + 1);

			if (last_node != nullptr) {
				last_node->suffix_link = new_node;
			}

			// Обновляем текущий узел и его дочерние узлы
			current_node->childs[line[current_edge]] = new_node;
			finded_node->left += current_length;

			new_node->childs[line[index]] = new Node(index, &suffix_end, root, index - remain + 1);
			new_node->childs[line[finded_node->left]] = finded_node;
			last_node = new_node;
		}
		// Обновляем переменные после обработки суффикса
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
	// Если пустая строка для поиска, вернем 0
	if (prompt.empty()) {
		return 0;
	}

	// Начинаем проход с корня
	Node* current_node = root;
	size_t depth = 0;
	int prompt_len = prompt.length();

	while (depth < prompt.length()) {
		auto finded_child = current_node->childs.find(prompt[depth]);

		// Если сына с нужным символом нет, вернем -1
		if (finded_child == current_node->childs.end()) {
			return -1;
		}
		Node* finded_node = finded_child->second;
		int node_len = suffix_length(finded_node);

		// Проверяем соответствие символов в найденном узле
		for (size_t i = 0; i < node_len; i++) {
			// Если достигли конца строки prompt, вернем индекс суффикса
			if (depth + i >= prompt_len) {
				return finded_node->suffix_index;
			}
			
			// Если символы не совпали, вернем -1
			if (prompt[depth + i] != line[finded_node->left + i]) {
				return -1;
			}
		}

		// Переходим к следующему узлу
		current_node = finded_node;
		depth += node_len;
	}
	return current_node->suffix_index;
}

void Suffix_tree::build(string text) {
	// Создаем корень
	root = new Node(-1, nullptr, nullptr, -1);
	
	// Удаляем корень, если он уже был
	if (!root->childs.empty()) { delete_node(root); }

	// Инициализировали текст и текущий узел
	line = text;
	current_node = root;

	// Добавляемм символы строки в суффиксное дерево
	for (size_t i = 0; line[i] != '\0'; i++) {
		update_tree(i);
	}

	// Обрабатываем конец строки
	update_tree(line.length());
}

void Suffix_tree::print(Node* start, int level) {
	// Проходим по всем дочерним узлам текущего узла
	for (pair<const char, Node*> mapa : start->childs) {
		// Пропускаем символ, если это конец строки
		if (mapa.first == '\0') {
			continue;
		}

		// Отступ для визуального представления глубины узла в дереве
		for (int i = 0; i < level; i++) {
			cout << "->";
		}

		// Выводим все символы узла
		for (int i = mapa.second->left; i <= *(mapa.second->right); i++) {
			cout << line[i];
		}
		cout << endl;

		// Если текущий узел имеет дочерние узлы, то рекурсивно вызываем функцию
		// для каждого дочернего узла, при этом увеличивая уровень
		if (!(start->childs.empty())) {
			print(mapa.second, level + 1);
		}
	}
}