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

    MatrixArr m2(3,4,{ 1,2,3,4,5,6,7,8,9,10,11,12 });
    cout << " -m2 = " << -m2 << endl;

    MatrixArr m3(2,3);
    cout << " m3 = " << m3 << endl;  

    cout << m2 << " == " << m1 << " -------- " << endl << boolalpha << (m2 == m1) << endl;
    cout << m1 << " != " << m3 << " -------- " << endl << boolalpha << (m1 != m3) << endl << endl;

    cout << "values matrix elements (0,0), (1,1), (2,2) is: " << m1(0, 0) << "," << m1(1, 1) << "," << m1(2, 2) << endl;
    m1(0, 0) = 10;
    m1(1, 1) = 11;
    m1(2, 2) = 12;
    cout << "change matrix elements (0,0), (1,1), (2,2) by: " << 10 << "," << 11 << "," << 12 << endl;
    cout << " --------";
    cout << m1 << endl;

    try
    {
        cout << "элементы матрицы:" << m1(1, 1) << m1(2, 2) << m1(3, 3) << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };

    // сложение матрицы и числа
    cout << m3 << " + ";
    cout << 3 << endl;
    cout << " -------- ";
    m3 += 3;
    cout << m3 << endl;

    // сложение матриц
    MatrixArr m4(3, 4, { 1,1,1,1,1,1,1,1,1,1,1,1});
    cout << m4 << " + " << m3 << " -------- " << (m4 + m3) << endl;

    cout << m1 << " + ";
    cout << m4 << " -------- ";
    cout << (m1 + m4) << endl;

    // вычитание матриц
    cout << m4 << " - " << m3 << " -------- " << (m4 - m3) << endl;

    cout << m1 << " - ";
    cout << m4 << " -------- ";
    cout << (m1 - m4) << endl;

    cout << "transpose:" << m4 << " -------- ";
    cout << m4.transpose() << endl;

    // умножение матрицы на число
    cout << m4 << " * " << 2 << endl; 
    cout << " -------- ";
    m4 *= 2;
    cout << m4 << endl;

    // умножение матриц
    cout << m1 << " * " << m1 << " -------- " << (m1 * m1) << endl;

    cout << m1;
    cout << " * ";
    cout << m4 << " -------- ";
    cout << (m1 * m4) << endl;

}

