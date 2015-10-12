#include <cstddef>
#include <iostream>
#include <iterator> 

class R3Vector 
{ 
public: 
    R3Vector() noexcept = default; 
    R3Vector(const R3Vector&) noexcept = default; 
    R3Vector(const double rX, const double rY, const double rZ); 
    ~R3Vector() noexcept = default;

    R3Vector& operator=(const R3Vector&) noexcept = default; 
    std::ostream& print(std::ostream& ostrm) const; 

    static constexpr ptrdiff_t dim() { return dimCount_;  } 
    double& operator[](const ptrdiff_t i); 
    const double& operator[](const ptrdiff_t i) const; 

    double x() const { return data_[0]; } 
    double y() const { return data_[1]; } 
    double z() const { return data_[2]; } 
    double& rx() { return data_[0]; } 
    double& ry() { return data_[1]; } 
    double& rz() { return data_[2]; } 

    R3Vector operator-(); 
    R3Vector& operator+=(const R3Vector& rhs); 
    R3Vector& operator+=(const double rhs); 
    R3Vector& operator-=(const R3Vector& rhs); 
    R3Vector& operator-=(const double rhs); 
    R3Vector& operator*=(const double rhs); 
    R3Vector& operator/=(const double rhs); 

    double* begin() { return data_; } 
    double* end() { return data_ + dimCount_; } 
    const double* cbegin() { return data_; } 
    const double* cend() { return data_ + dimCount_; } 
private: 
    static const ptrdiff_t dimCount_{3}; 
    double data_[dimCount_] = {0.0}; 
}; 

    R3Vector operator+(const R3Vector& lhs, const R3Vector& rhs) { return R3Vector(lhs) += rhs; } 
    R3Vector operator+(const R3Vector& lhs, const double rhs) { return R3Vector(lhs) += rhs;} 
    R3Vector operator-(const R3Vector& lhs, const R3Vector& rhs) { return R3Vector(lhs) -= rhs; } 
    R3Vector operator-(const R3Vector& lhs, const double rhs) { return R3Vector(lhs) -= rhs; } 
    R3Vector operator*(const R3Vector& lhs, const double rhs) { return R3Vector(lhs) *= rhs; } 
    R3Vector operator*(const double lhs, const R3Vector& rhs) { return R3Vector(rhs) *= lhs; } 
    R3Vector operator/(const R3Vector& lhs, const double rhs) { return R3Vector(lhs) /= rhs; } 

    bool operator==(const R3Vector& lhs, const R3Vector& rhs); 
    bool operator!=(const R3Vector& lhs, const R3Vector& rhs); 

    std::ostream& operator<<(std::ostream& ostrm, const R3Vector& v);

using namespace std;

void testVectorByIndexRead(const R3Vector& v, const ptrdiff_t i) 
{ 
    try 
    { 
        cout << "read v[" << i << "] -> "; 
        cout << v[i]; 
    } 
    catch (const out_of_range& ex) 
    { 
        cout << "exception caught " << ex.what(); 
    } 
} 

int main() 
{ 
    constexpr ptrdiff_t nSize{3 * R3Vector::dim()}; 
    R3Vector v0; 
    cout << v0 << endl;
    cout << "x=" << v0.x() << " y=" << v0.y() << " z=" << v0.z() << endl; 
    R3Vector v1{ 0.2, 0.6, -5.8 }; 
    cout << "v1 = " << v1 << endl; 
    R3Vector v2{v1}; 
    cout << "v2 = " << v2 << endl;
    //cout << v2 << endl; 
    v2.rx() *= 2; 
    v2.ry() *= 2; 
    v2.rz() *= 2; 
    cout << "v2*2 = " << v2 << endl;

    for (ptrdiff_t i{-2}; i <= v2.dim(); i += 1) 
    { 
        testVectorByIndexRead(v2, i); 
        cout << endl; 
    } 

    double scale{1.2}; 
    cout << v2 << " * " << scale << " -> " << flush; 
    cout << (v2 * scale) << endl; 

    //DONE
    // присваивание
    R3Vector v3;
    v3 = v2;
    cout << " v3 = " << v3 << endl << endl;
    // сравнение
    cout << v2 << " == " << v3 << " -> " << boolalpha << (v2 == v3) << endl << endl;
    cout << v1 << " != " << v3 << " -> " << boolalpha << (v1 != v3) << endl << endl;
    // отрицание
    cout << " -v2 =" << -v2 << endl << endl;
    // сложение векторов
    cout << v2 << " + " << v3 << " -> " << (v2 + v3) << endl << endl;
    // сложение вектора и числа
    cout << v2 << " + " << 0.9 << " -> " << (v2 + 0.9) << endl << endl;
    // вычитание векторов
    cout << v3 << " - " << v1 << " -> " << (v3 - v1) << endl << endl;
    // вычитание вектора и числа
    cout << v3 << " - " << 1.0 << " -> " << (v3 - 1.0) << endl << endl;
    // умножение вектора на число
    cout << v1 << " * " << 2.5 << " -> " << (v1 * 2.5) << endl << endl;
    cout << 2.5 << " * " << v1 << " -> " << (2.5 * v1) << endl << endl;
    // деление вектора на число
    cout << v2 << " / " << 2 << " -> " << (v2 / 2) << endl;

    return 0;
} 

R3Vector::R3Vector(const double rX, const double rY, const double rZ) 
    : data_{rX, rY, rZ} 
{ 
} 

std::ostream& R3Vector::print(std::ostream& ostrm) const 
{ 
    return ostrm << '(' << x() << ',' << y() << ',' << z() << ')'; 
} 

double& R3Vector::operator[](const ptrdiff_t i) 
{ 
    if ((i < 0) || (dim() <= i)) 
    throw out_of_range("Index out of range in R3Vector::operator[]()."); 
    return data_[i]; 
} 

const double& R3Vector::operator[](const ptrdiff_t i) const 
{ 
    if ((i < 0) || (dim() <= i)) 
    throw out_of_range("Index out of range in R3Vector::operator[]() const."); 

    return data_[i]; 
} 

R3Vector R3Vector::operator-() 
{ 
    return {-x(), -y(), -z()}; 
} 

R3Vector& R3Vector::operator+=(const R3Vector& rhs) 
{ 
    for (ptrdiff_t i{0}; i != dim(); i += 1) 
    { 
        data_[i] += rhs.data_[i]; 
    } 
    return *this; 
} 

R3Vector& R3Vector::operator+=(const double rhs) 
{ 
    for (auto& v : *this) 
    { 
        v += rhs; 
    } 
    return *this; 
} 

R3Vector& R3Vector::operator-=(const R3Vector& rhs) 
{ 
    rx() -= rhs.x(); 
    ry() -= rhs.y(); 
    rz() -= rhs.z(); 
    return *this; 
} 

R3Vector& R3Vector::operator-=(const double rhs) 
{ 
    for (auto iCur{begin()}, iEnd{end()}; iCur != iEnd; ++iCur) 
    { 
        *iCur -= rhs; 
    } 
    return *this; 
} 

std::ostream& operator<<(std::ostream& ostrm, const R3Vector& v) 
{ 
    return v.print(ostrm); 
} 

R3Vector& R3Vector::operator*=(const double rhs) 
{ 
    rx() *= rhs; 
    ry() *= rhs; 
    rz() *= rhs; 
    return *this; 
} 

R3Vector& R3Vector::operator/=(const double rhs) 
{ 
    for (auto& coord : *this) 
    { 
        coord /= rhs; 
    } 
    return *this; 
}

// оператор равенства
bool operator==(const R3Vector& lhs, const R3Vector& rhs) 
{
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y()) && (lhs.z() == rhs.z());
}
// неравенство
bool operator!=(const R3Vector& lhs, const R3Vector& rhs) 
{
    return !(lhs == rhs);
}


