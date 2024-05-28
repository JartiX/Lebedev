﻿#include <iostream>
#include "Suffix_tree/suffix_tree.hpp"

using namespace std;


int main() {
    setlocale(LC_ALL, "ru-RU");
    Suffix_tree a;

    a.build("abcabxabcd"); // построение дерева
    cout << "A:" << endl;
    a.print(a.root, 0); // вывод дерева
    cout << endl;
    cout << "Последнее вхождение bc в a: " << a.find("bc") << endl; // поиск подстроки. возвращает последнее вхождение
    cout << endl;

    Suffix_tree b;
    b.build("9283xabcd");
    cout << "B:" << endl;
    b.print(b.root, 0);
    cout << endl;

    cout << endl << "A and B similarity: " << (a == b) << "%" << endl;
    cout << endl;

    Suffix_tree c;
    c.build("7777bxabcd");
    cout << "C:" << endl;
    c.print(c.root, 0);
    cout << endl;

    cout << endl << "A and C similarity: " << (a == c) << "%" << endl;

    return 0;
}
