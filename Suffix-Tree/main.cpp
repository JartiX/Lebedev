#include <iostream>
#include "Suffix_tree/suffix_tree.hpp"

using namespace std;


int main() {
    setlocale(LC_ALL, "ru-RU");
    Suffix_tree test_many_builds;
    test_many_builds.build("1246");
    test_many_builds.build("1247");
    test_many_builds.print(test_many_builds.Get_root(), 0);
    cout << endl;

    Suffix_tree a;

    a.build("abcabxabcd"); // построение дерева
    cout << "A:" << endl;
    a.print(a.Get_root(), 0); // вывод дерева
    cout << endl;
    cout << "Last entry index of {bc} in a: " << a.find("bc") << endl; // поиск подстроки. возвращает последнее вхождение
    cout << endl;

    Suffix_tree b;
    b.build("9283xabcd");
    cout << "B:" << endl;
    b.print(b.Get_root(), 0);
    cout << endl;

    cout << endl << "A and B similarity: " << (a == b) << "%" << endl;
    cout << endl;

    Suffix_tree c;
    c.build("7777bxabcd");
    cout << "C:" << endl;
    c.print(c.Get_root(), 0);
    cout << endl;

    cout << endl << "A and C similarity: " << (a == c) << "%" << endl;

    cout << "Number of entries of line {ab} in a: " << a.count_substring_entry("ab") << " times" << endl;

    cout << "Is entry {cabx} in a: " << a.is_contain("cabx") << endl;

    Suffix_tree bb("1352436s");
    cout << endl;
    bb.print(bb.Get_root(), 0);

    Suffix_tree kk;
    cout << "Enter string: ";
    cin >> kk;
    kk.print(kk.Get_root(), 0);

    cout << "Enter string: ";
    cin >> kk;
    kk.print(kk.Get_root(), 0);

    return 0;
}
