#include <iostream>
#include "Suffix_tree/suffix_tree.hpp"

using namespace std;


int main() {
    setlocale(LC_ALL, "ru-RU");
    Suffix_tree a;

    a.build("abcabxabcd"); // построение дерева
    cout << a.find("xab") << endl; // поиск подстроки. возвращает последнее вхождение
    a.print(a.root, 0); // вывод дерева
    return 0;
}
