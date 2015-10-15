#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iostream> // ***
#include <cstddef>
#include <cstdint> 
#include <initializer_list>
#include <memory> 

using ValueType = int32_t;
using IndexType = ptrdiff_t;

class ZnVectorD 
{ 
public: 
    ZnVectorD() = default;
    ZnVectorD(const IndexType dims);
    ZnVectorD(std::initializer_list<ValueType> list); 
    ZnVectorD(const ZnVectorD& vec); 
    ZnVectorD(ZnVectorD&& vec); 

    ~ZnVectorD();

    ZnVectorD& operator=(const ZnVectorD& vec); 
    ZnVectorD& operator=(ZnVectorD&& vec); 

    // *** 
    IndexType dim() { return dims_; }

    // изменение размера вектора
    ZnVectorD& resize(IndexType newSize)
    {
        if (newSize > 0 && newSize != dims_) {
            ZnVectorD tmp(newSize);
            for (IndexType i{ 0 }; i < (dims_ > newSize ? newSize : dims_); i += 1)
            {
                tmp.data_[i] = data_[i];
            }
            swap(tmp);
            tmp.dims_ = 0;
            tmp.data_ = nullptr;
        }
        return *this;
    }

    std::ostream& print(std::ostream& ostrm) const;

    ZnVectorD operator-();
    ZnVectorD& operator+=(const ZnVectorD& rhs); 
    ZnVectorD& operator+=(const ValueType rhs); 
    ZnVectorD& operator-=(const ZnVectorD& rhs); 
    ZnVectorD& operator-=(const ValueType rhs); 
    ZnVectorD& operator*=(const ValueType rhs); 
    ZnVectorD& operator/=(const ValueType rhs); 

    ValueType& operator[](const IndexType index); 
    const ValueType& operator[](const IndexType index) const;

    ValueType* begin() { return data_; } 
    ValueType* end() { return data_ + dims_; } 
    const ValueType* cbegin() { return data_; } 
    const ValueType* cend() { return data_ + dims_; } 

private: 
    IndexType  dims_{0}; 
    ValueType* data_{nullptr}; 
private: 
    void swap(ZnVectorD& arr); 
}; 

// *** 
ZnVectorD operator+(ZnVectorD& lhs, ZnVectorD& rhs);
ZnVectorD operator+(ZnVectorD& lhs, const ValueType rhs);
ZnVectorD operator-(ZnVectorD& lhs, ZnVectorD& rhs);
ZnVectorD operator-(ZnVectorD& lhs, const ValueType rhs);
ZnVectorD operator*(ZnVectorD& lhs, const ValueType rhs);
ZnVectorD operator*(const ValueType lhs, ZnVectorD& rhs);
ZnVectorD operator/(ZnVectorD& lhs, const ValueType rhs);

bool operator==(ZnVectorD& lhs, ZnVectorD& rhs);
bool operator!=(ZnVectorD& lhs, ZnVectorD& rhs);

std::ostream& operator<<(std::ostream& ostrm, const ZnVectorD& v);

//===============================================================

using namespace std;

int main() 
{ 
	// TODO 
    // конструкторы
    ZnVectorD v0;
    cout << " v0 = " << v0 << endl; 
    ZnVectorD v1{1,2,3,4};
    ZnVectorD v2{-1,-2,-3,-4,-5,-6 };
    cout << " v1 = " << v1 << endl; // *** 
    cout << " v2 = " << v2 << endl; // *** 
    ZnVectorD v3(8);
    cout << " v3 = " << v3 << endl;  
    ZnVectorD v4{ v1 };
    cout << " v4 = " << v4 << endl;
    v4.resize(9);
    cout << " resize(9) v4 = " << v4 << endl;
    v4.resize(3);
    cout << " resize(3) v4 = " << v4 << endl;
    v4.resize(0);
    cout << " resize(0) v4 = " << v4 << endl;
    v4.resize(-1);
    cout << "resize(-1) v4 = " << v4 << endl;
    ZnVectorD v5{ (v1 + v4) };
    cout << " v5 = " << v5 << endl;
   
    // присваивание
    v3 = v2;
    cout << " v3 = v2 -> " << v3 << endl << endl;
    // сравнение
    cout << v1 << " == " << v4 << " -> " << boolalpha << (v1 == v4) << endl;
    cout << v1 << " == " << -v3 << " -> " << boolalpha << (v1 == (-v3)) << endl;
    cout << v2 << " != " << v3 << " -> " << boolalpha << (v2 != v3) << endl << endl;
    // сложение векторов
    cout << v2 << " + " << v3 << " -> " << (v2 + v3) << endl;
    cout << v1 << " + " << v2 << " -> " << (v1 + v2) << endl;
    // сложение вектора и числа
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

    return 0;
}

//=================================================================

ZnVectorD::ZnVectorD(const IndexType dims) 
    : dims_{dims} 
{ 
    data_ = new ValueType[dims_]{0};
} 

ZnVectorD::ZnVectorD(const ZnVectorD& vec) 
    : dims_{vec.dims_} 
    , data_{new ValueType[dims_]} 
{ 
    std::uninitialized_copy(vec.data_, vec.data_ + vec.dims_, data_); 
} 

ZnVectorD::ZnVectorD(ZnVectorD&& vec) 
    : dims_{vec.dims_} 
    , data_{vec.data_} 
{ 
    vec.dims_ = 0; 
    vec.data_ = nullptr; 
} 

ZnVectorD::ZnVectorD(std::initializer_list<ValueType> vals) 
    : dims_{static_cast<IndexType>(vals.size())} 
    , data_{new ValueType[dims_]} 
{ 
    std::uninitialized_copy(vals.begin(), vals.end(), data_); 
} 

ZnVectorD::~ZnVectorD() 
{ 
    delete[] data_; 
} 

ZnVectorD& ZnVectorD::operator=(const ZnVectorD& arr) 
{ 
    if (this != &arr) 
    { 
        swap(ZnVectorD(arr)); 
    } 
    return *this; 
} 

ZnVectorD& ZnVectorD::operator=(ZnVectorD&& arr) 
{ 
    if (this != &arr) 
    { 
        swap(arr); 
    } 
    return *this; 
} 

// ***
std::ostream& ZnVectorD::print(std::ostream& ostrm) const
{
    cout << '(';
    if (dims_ != 0)
    {
        for (IndexType i{ 0 }; i < dims_ - 1; i += 1)
        {
            cout << data_[i] << ',';
        }
        cout << data_[dims_ - 1];
    };
    cout << ')';
    return ostrm;
}

ValueType& ZnVectorD::operator[](const IndexType index) 
{ 
    assert(index <= 0); 
    assert(index < dims_); 
    if ((index < 0) || (dims_ <= index)) 
    { 
        throw out_of_range("index out of range in ZnVectorD::operator[]"); 
    } 
    return data_[index]; 
} 

const ValueType& ZnVectorD::operator[](const IndexType index) const 
{ 
    assert(index <= 0); 
    assert(index < dims_); 
    if ((index < 0) || (dims_ <= index)) 
    { 
        throw out_of_range("index out of range in ZnVectorD::operator[]"); 
    } 
    return data_[index]; 
} 

void ZnVectorD::swap(ZnVectorD& arr) 
{ 
    IndexType dims{arr.dims_}; 
    arr.dims_ = dims_; 
    dims_ = dims; 
    ValueType* data{arr.data_}; 
    arr.data_ = data_; 
    data_ = data; 
} 

ZnVectorD ZnVectorD::operator-() 
{ 
    ZnVectorD res(dims_); 
    for (IndexType i{0}; i < dims_; i += 1) 
    { 
        res.data_[i] = -data_[i]; 
    } 
    return res; 
} 

ZnVectorD& ZnVectorD::operator+=(const ZnVectorD& rhs) 
{ 
    // TODO 
    for (IndexType i{ 0 }; i != dims_; ++i)
    {
        data_[i] += rhs.data_[i];
    }
    return *this; 
} 

ZnVectorD& ZnVectorD::operator+=(const ValueType rhs) 
{ 
    for_each(data_, data_ + dims_, [rhs](ValueType& v){ v += rhs; }); 
    return *this; 
} 

ZnVectorD& ZnVectorD::operator-=(const ZnVectorD& rhs) 
{ 
    for (IndexType i{0}; i != dims_; ++i) 
    { 
        data_[i] -= rhs.data_[i]; 
    } 
    return *this; 
} 

ZnVectorD& ZnVectorD::operator-=(const ValueType rhs) 
{ 
    for (IndexType i{0}; i != dims_; ++i) 
    { 
        data_[i] -= rhs; 
    } 
    return *this; 
} 

ZnVectorD& ZnVectorD::operator*=(const ValueType rhs) 
{ 
    for (ValueType* v{data_}, *vEnd{data_ + dims_}; v != vEnd; ++v) 
    { 
        *v *= rhs; 
    } 
    return *this; 
} 

ZnVectorD& ZnVectorD::operator/=(const ValueType rhs) 
{ 
    // TODO 
    for (ValueType* v{ data_ }, *vEnd{ data_ + dims_ }; v != vEnd; ++v)
    {
        *v /= rhs;
    }
    return *this; 
}

// ***
// оператор сложения
ZnVectorD operator+(ZnVectorD& lhs, ZnVectorD& rhs)
{
    if (lhs.dim() == rhs.dim()) return ZnVectorD(lhs) += rhs;
    try {
        throw std::runtime_error("Mismatch ZnVectorD dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch ZnVectorD dimensions: " ;
    }
    return lhs;
};

ZnVectorD operator+(ZnVectorD& lhs, const ValueType rhs) { return ZnVectorD(lhs) += rhs; }

// оператор разности
ZnVectorD operator-(ZnVectorD& lhs, ZnVectorD& rhs)
{
    if (lhs.dim() == rhs.dim()) return ZnVectorD(lhs) -= rhs;
    try {
        throw std::runtime_error("Mismatch ZnVectorD dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch ZnVectorD dimensions: ";
    }
    return lhs;
};

ZnVectorD operator-(ZnVectorD& lhs, const ValueType rhs) { return ZnVectorD(lhs) -= rhs; }
// оператор умножения вектора на число
ZnVectorD operator*(ZnVectorD& lhs, const ValueType rhs) { return ZnVectorD(lhs) *= rhs; }
ZnVectorD operator*(const ValueType lhs, ZnVectorD& rhs) { return ZnVectorD(rhs) *= lhs; }
// оператор деления вектора на число
ZnVectorD operator/(ZnVectorD& lhs, const ValueType rhs) { return ZnVectorD(lhs) /= rhs; }

// оператор равенства
bool operator==(ZnVectorD& lhs, ZnVectorD& rhs)
{
    if (lhs.dim() == rhs.dim())
    {
        for (IndexType i{ 0 }; i < rhs.dim(); i += 1)
        {
            if (*(lhs.begin() + i) != *(rhs.begin() + i))
            {
                return false;
            };
        }
        return true;
    }
    else return false;
}

// неравенство
bool operator!=(ZnVectorD& lhs, ZnVectorD& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& ostrm, const ZnVectorD& v)
{
    return v.print(ostrm);
}

