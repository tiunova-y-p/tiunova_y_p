#include "znvectort.cpp" 
#include <iostream> 

using namespace std;

int main() 
{ 
    cout << "ZnVectorT<int32_t, ptrdiff_t>" << endl;
    // конструкторы
    ZnVectorT<int32_t, ptrdiff_t> v0;
    cout << " v0 = " << v0 << endl; 
    ZnVectorT<int32_t, ptrdiff_t> v1{1,2,3,4};
    ZnVectorT<int32_t, ptrdiff_t> v2{-1,-2,-3,-4,-5,-6 };
    cout << " v1 = " << v1 << endl;  
    cout << " v2 = " << v2 << endl; 
    ZnVectorT<int32_t, ptrdiff_t> v3(8);
    cout << " v3 = " << v3 << endl;  
    ZnVectorT<int32_t, ptrdiff_t> v4{ v1 };
    cout << " v4 = " << v4 << endl;

    // присваивание
    v3 = -v2;
    cout << " v3 = -v2 -> " << v3 << endl << endl;
    // сравнение
    cout << v1 << " == " << v4 << " -> " << boolalpha << (v1 == v4) << endl;
    cout << v1 << " == " << -v3 << " -> " << boolalpha << (v1 == (-v3)) << endl;
    cout << v2 << " != " << v3 << " -> " << boolalpha << (v2 != v3) << endl << endl;
    // сложение векторов
    cout << v2 << " + " << v3 << " -> " << (v2 + v3) << endl;
    cout << v1 << " + " << v2 << " -> " << (v1 + v2) << endl;

    // сложение вектора и числа
    v2 += 3;
    cout << "v2 += 3 -> " << v2 << endl;
    v1 += v4;
    cout << "v1 += v4 -> " << v1 << endl;
    cout << v2 << " + " << 3 << " -> " << (v2 + 3) << endl << endl;
    // вычитание векторов
    cout << v3 << " - " << v1 << " -> " << (v3 - v1) << endl;
    cout << v3 << " - " << v2 << " -> " << (v3 - v2) << endl;
    // вычитание вектора и числа
    cout << v3 << " - " << 2 << " -> " << (v3 - 2) << endl << endl;
    // умножение вектора на число
    cout << v1 << " * " << 3 << " -> " << (v1 * 3) << endl;
    cout << 3 << " * " << v2 << " -> " << (3 * v2) << endl << endl;
    // деление вектора на число
    cout << v2 << " / " << 2 << " -> " << (v2 / 2) << endl;
    cout << endl << endl;

    cout << "ZnVectorT<int, double>" << endl;
    // конструкторы
    ZnVectorT<int, double> w0;
    cout << " w0 = " << w0 << endl;
    ZnVectorT<int, double> w1{ 1.1,2.2,3.3,4.4 };
    ZnVectorT<int, double> w2{ -1.5,-2.5,-3.5,-4.5,-5.5,-6.5 };
    cout << " w1 = " << w1 << endl;
    cout << " w2 = " << w2 << endl;
    ZnVectorT<int, double> w3(8);
    cout << " w3 = " << w3 << endl;
    ZnVectorT<int, double> w4{ w1 };
    cout << " w4 = " << w4 << endl;

    // присваивание
    w3 = -w2;
    cout << " w3 = -w2 -> " << w3 << endl << endl;
    // сравнение
    cout << w1 << " == " << w4 << " -> " << boolalpha << (w1 == w4) << endl;
    cout << w1 << " == " << -w3 << " -> " << boolalpha << (w1 == (-w3)) << endl;
    cout << w2 << " != " << w3 << " -> " << boolalpha << (w2 != w3) << endl << endl;
    // сложение векторов
    cout << w2 << " + " << w3 << " -> " << (w2 + w3) << endl;
    cout << w1 << " + " << w2 << " -> " << (w1 + w2) << endl;

    // сложение вектора и числа
    w2 += 3;
    cout << "w2 += 3 -> " << w2 << endl;
    w1 += w4;
    cout << "w1 += w4 -> " << w1 << endl;
    cout << w2 << " + " << 3 << " -> " << (w2 + 3.) << endl << endl;
    // вычитание векторов
    cout << w3 << " - " << w1 << " -> " << (w3 - w1) << endl;
    cout << w3 << " - " << w2 << " -> " << (w3 - w2) << endl;
    // вычитание вектора и числа
    cout << w3 << " - " << 2 << " -> " << (w3 - 2.) << endl << endl;
    // умножение вектора на число
    cout << w1 << " * " << 3 << " -> " << (w1 * 3.) << endl;
    cout << 3 << " * " << w2 << " -> " << (3. * w2) << endl << endl;
    // деление вектора на число
    cout << w2 << " / " << 2 << " -> " << (w2 / 2.) << endl;

}

