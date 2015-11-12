#include "matrixarr.h" 
#include <iostream> // ***

using namespace std;

int main() 
{ 
    // конструкторы
    MatrixArr m0;
    cout << " m0 = " << m0 << endl; 

    MatrixArr m1(3,4,{1,2,3,4,5,6,7,8,9,10,11,12});
    cout << " m1 = " << m1 << endl;

    MatrixArr m3(2,3);
    cout << " m3 = " << m3 << endl;  

    cout << m3 << " == " << -m1 << " -> " << boolalpha << (m3 == (-m1)) << endl;
    cout << m1 << " != " << m3 << " -> " << boolalpha << (m1 != m3) << endl << endl;
 
    // сложение векторов
    MatrixArr m2(3, 4, { 1,1,1,1,1,1,1,1,1,1,1,1});
    cout << m2 << " + " << m3 << " -> " << (m2 + m3) << endl;
    cout << m1 << " + " << m2 << " -> " << (m1 + m2) << endl;

    //// сложение вектора и числа
    //cout << m2 << " + " << 3 << " -> " << (m2 + 3) << endl << endl;
    //// вычитание векторов
    //cout << m3 << " - " << m1 << " -> " << (m3 - m1) << endl;
    //cout << m3 << " - " << m2 << " -> " << (m3 - m2) << endl;
    //// вычитание вектора и числа
    //cout << m3 << " - " << 2 << " -> " << (m3 - 2) << endl << endl;
    //// умножение вектора на число
    //cout << m1 << " * " << 3 << " -> " << (m1 * 3) << endl;
    //cout << 3 << " * " << m2 << " -> " << (3 * m2) << endl << endl;

}

