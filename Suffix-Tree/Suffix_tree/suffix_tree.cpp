#include "suffix_tree.hpp"

using namespace std;


int suffix_tree::suffix_length(node* node) const {
    if (node == root) return 0;
    return *node->right - node->left + 1;
}

void suffix_tree::build(string data) {
    root = new node(-1, nullptr, nullptr, -1);

    if (!root->childs.empty()) del(root);
    line = data;
    active_node = root;

    for (int i = 0; line[i] != '\0'; i++) {
        update_tree(i);
    }
    update_tree(line.length());
}

void suffix_tree::del(node* node) {
    for (auto i : node->childs) {
        del(i.second);
    }
    if (node->suffix_index == -1) delete node->right;
    delete node;
}

void suffix_tree::update_tree(int index) {

    last_created = nullptr;
    remain++;
    suffix_end++;

    while (remain != 0) {
        // задаем активное ребро
        if (active_length == 0) {
            active_edge = index;
        }
        // ищем суффикс который начинается на данный символ
        auto finded_child = active_node->childs.find(line[active_edge]);

        // если нет суффикса который начинается на данный символ
        if (finded_child == active_node->childs.end()) {
            node* added_letter = new node(index, &suffix_end, root, index - remain + 1);
            active_node->childs.insert(make_pair(line[index], added_letter));
            if (last_created != nullptr) {
                last_created->suffix_link = active_node;
                last_created = nullptr;
            }
        }
        else {
            node* finded_node = finded_child->second;

            // если можем спуститься к ноде - спускаемся
            if (active_length >= suffix_length(finded_node)) {
                active_node = finded_node;
                active_length -= suffix_length(finded_node);
                active_edge += suffix_length(finded_node);
                continue;
            }

            //если можем спуститься по ребру - спускаемся
            if (line[index] == line[finded_child->second->left + active_length]) {
                if (last_created != nullptr && active_node != root) last_created->suffix_link = active_node;
                active_length++;
                break;
            }

            // деление ребра
            node* new_node = new node(finded_node->left, new int(finded_node->left + active_length - 1), root, index - remain + 1);
            
            // создаем суффиксную ссылку
            if (last_created != nullptr) last_created->suffix_link = new_node;
            active_node->childs[line[active_edge]] = new_node;
            finded_node->left += active_length;
            new_node->childs.insert(make_pair(line[index], new node(index, &suffix_end, root, index - remain + 1)));
            new_node->childs.insert(make_pair(line[finded_node->left], finded_node));
            last_created = new_node;
        }
        remain--;

        if (active_length > 0 && active_node == root) {
            active_length--;
            active_edge++;
        }
        else if (active_node != root) {
            active_node = active_node->suffix_link;
        }
    }
}

void suffix_tree::print(node* start, int lvl) {
    // перебор нод
    for (auto i : start->childs) {
        if (i.first == '\0') continue;
        for (int k = 0; k < lvl; k++) {
            cout << "->";
        }

        // вывод суффикса
        for (int j = i.second->left; j <= *(i.second->right); j++) {
            cout << line[j];
        }
        cout << endl;

        // спуск по детям
        if (!(start->childs.empty())) {
            print(i.second, lvl + 1);
        }
    }
}

int suffix_tree::find(string text) {
    if (text.empty()) return 0;

    node* current_node = root;
    size_t depth = 0;
    int text_length = text.length();

    while (depth < text.length()) {
        auto finded_child = current_node->childs.find(text[depth]);
        if (finded_child == current_node->childs.end()) return -1;
        node* finded_node = finded_child->second;
        int node_length = suffix_length(finded_node);

        for (int i = 0; i < node_length; i++) {
            if (depth + i >= text_length) return finded_node->suffix_index;
            if (text[depth + i] != line[finded_node->left + i]) return -1;
        }

        current_node = finded_node;
        depth += node_length;
    }
    return current_node->suffix_index;
}
