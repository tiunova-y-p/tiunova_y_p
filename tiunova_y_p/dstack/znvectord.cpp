#include "znvectord.h" 

#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iostream> // ***

using namespace std; 

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

