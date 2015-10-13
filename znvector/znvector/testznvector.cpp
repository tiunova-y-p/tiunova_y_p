#include "znvector.h" 
#include <iostream> // ***

using namespace std;

int main() 
{ 
	// TODO 
    // ������������
    ZnVector v0;
    cout << " v0 = " << v0 << endl; 
    ZnVector v1{1,2,3,4};
    ZnVector v2{-1,-2,-3,-4,-5,-6 };
    cout << " v1 = " << v1 << endl; // *** 
    cout << " v2 = " << v2 << endl; // *** 
    ZnVector v3(8);
    cout << " v3 = " << v3 << endl;  
    ZnVector v4{ v1 };
    cout << " v4 = " << v4 << endl;
    ZnVector v5{ (v1 + v4) };
    cout << " v5 = " << v5 << endl;

    // ������������
    v3 = v2;
    cout << " v3 = v2 -> " << v3 << endl << endl;
    // ���������
    cout << v1 << " == " << v4 << " -> " << boolalpha << (v1 == v4) << endl;
    cout << v1 << " == " << -v3 << " -> " << boolalpha << (v1 == (-v3)) << endl;
    cout << v2 << " != " << v3 << " -> " << boolalpha << (v2 != v3) << endl << endl;
    // �������� ��������
    cout << v2 << " + " << v3 << " -> " << (v2 + v3) << endl;
    cout << v1 << " + " << v2 << " -> " << (v1 + v2) << endl;
    // �������� ������� � �����
    cout << v2 << " + " << 3 << " -> " << (v2 + 3) << endl << endl;
    // ��������� ��������
    cout << v3 << " - " << v1 << " -> " << (v3 - v1) << endl;
    cout << v3 << " - " << v2 << " -> " << (v3 - v2) << endl;
    // ��������� ������� � �����
    cout << v3 << " - " << 2 << " -> " << (v3 - 2) << endl << endl;
    // ��������� ������� �� �����
    cout << v1 << " * " << 3 << " -> " << (v1 * 3) << endl;
    cout << 3 << " * " << v2 << " -> " << (3 * v2) << endl << endl;
    // ������� ������� �� �����
    cout << v2 << " / " << 2 << " -> " << (v2 / 2) << endl;
}

