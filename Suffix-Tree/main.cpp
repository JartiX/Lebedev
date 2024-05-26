#include <iostream>
#include "Suffix_tree/suffix_tree.hpp"

using namespace std;


int main() {
    suffix_tree a;

    a.build("abcabxabcd"); // ���������� ������
    cout << a.find("xab") << endl; // ����� ���������. ���������� ��������� ���������
    a.print(a.root, 0); // ����� ������
    return 0;
}
