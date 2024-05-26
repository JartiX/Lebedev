#include <iostream>
#include "Suffix_tree/suffix_tree.hpp"

using namespace std;


int main() {
    suffix_tree a;

    a.build("abcabxabcd"); // построение дерева
    cout << a.find("xab") << endl; // поиск подстроки. возвращает последнее вхождение
    a.print(a.root, 0); // вывод дерева
    return 0;
}
