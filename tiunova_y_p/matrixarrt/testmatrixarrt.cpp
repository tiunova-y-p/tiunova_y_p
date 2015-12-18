#include "matrixarrt.cpp" 
#include <iostream> 

using namespace std;

int main() 
{ 
    // конструкторы
    MatrixArrT<int32_t, ptrdiff_t> m0;
    cout << " m0 = " << m0 << endl; 

    MatrixArrT<int32_t, ptrdiff_t> m1(3,4,{1,2,3,4,5,6,7,8,9,10,11,12});
    cout << " m1 = " << m1 << endl;

    MatrixArrT<int32_t, ptrdiff_t> m2(3,4,{ 1,2,3,4,5,6,7,8,9,10,11,12 });
    cout << " -m2 = " << -m2 << endl;

    MatrixArrT<int32_t, ptrdiff_t> m3(2,3);
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
    MatrixArrT<int32_t, ptrdiff_t> m4(3, 4, { 1,1,1,1,1,1,1,1,1,1,1,1});
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


    // конструкторы
    MatrixArrT<int, double> md0;
    cout << " md0 = " << md0 << endl;

    MatrixArrT<int, double> md1(3, 4, { 1.1,2.3,3.2,4.1,5.4,6.1,7.3,8.4,9.2,10.1,11.3,12.5 });
    cout << " md1 = " << md1 << endl;

    MatrixArrT<int, double> md2(3, 4, { 1.1,2.3,3.2,4.1,5.4,6.1,7.3,8.4,9.2,10.1,11.3,12.5 });
    cout << " -md2 = " << -md2 << endl;

    MatrixArrT<int, double> md3(2, 3);
    cout << " md3 = " << md3 << endl;

    cout << md2 << " == " << md1 << " -------- " << endl << boolalpha << (md2 == md1) << endl;
    cout << md1 << " != " << md3 << " -------- " << endl << boolalpha << (md1 != md3) << endl << endl;

    cout << "values matrix elements (0,0), (1,1), (2,2) is: " << md1(0, 0) << "," << md1(1, 1) << "," << md1(2, 2) << endl;
    md1(0, 0) = 10.1;
    md1(1, 1) = 11.2;
    md1(2, 2) = 12.3;
    cout << "change matrix elements (0,0), (1,1), (2,2) by: " << 10.1 << "," << 11.2 << "," << 12.3 << endl;
    cout << " --------";
    cout << md1 << endl;

    try
    {
        cout << "элементы матрицы:" << md1(1, 1) << md1(2, 2) << md1(3, 3) << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Exception caught (" << e.what() << ')' << endl;
    };

    // сложение матрицы и числа
    cout << md3 << " + ";
    cout << 3 << endl;
    cout << " -------- ";
    md3 += 3;
    cout << md3 << endl;

    // сложение матриц
    MatrixArrT<int, double> md4(3, 4, { 1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1,1.1 });
    cout << md4 << " + " << md3 << " -------- " << (md4 + md3) << endl;

    cout << md1 << " + ";
    cout << md4 << " -------- ";
    cout << (md1 + md4) << endl;

    // вычитание матриц
    cout << md4 << " - " << md3 << " -------- " << (md4 - md3) << endl;

    cout << md1 << " - ";
    cout << md4 << " -------- ";
    cout << (md1 - md4) << endl;

    cout << "transpose:" << md4 << " -------- ";
    cout << md4.transpose() << endl;

    // умножение матрицы на число
    cout << md4 << " * " << 2.5 << endl;
    cout << " -------- ";
    md4 *= 2.5;
    cout << md4 << endl;

    // умножение матриц
    cout << md1 << " * " << md1 << " -------- " << (md1 * md1) << endl;

    cout << md1;
    cout << " * ";
    cout << md4 << " -------- ";
    cout << (md1 * md4) << endl;

}

