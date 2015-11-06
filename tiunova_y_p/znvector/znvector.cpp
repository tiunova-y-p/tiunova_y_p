#include "znvector.h" 

#include <cassert>
#include <algorithm>
#include <stdexcept>
#include <iostream> // ***

using namespace std; 

using ValueType = int32_t;
using IndexType = ptrdiff_t;

ZnVector::ZnVector(const IndexType dims) 
    : dims_{dims} 
{ 
    data_ = new ValueType[dims_]{0};
} 

ZnVector::ZnVector(const ZnVector& vec) 
    : dims_{vec.dims_} 
    , data_{new ValueType[dims_]} 
{ 
    std::uninitialized_copy(vec.data_, vec.data_ + vec.dims_, data_); 
} 

ZnVector::ZnVector(ZnVector&& vec) 
    : dims_{vec.dims_} 
    , data_{vec.data_} 
{ 
    vec.dims_ = 0; 
    vec.data_ = nullptr; 
} 

ZnVector::ZnVector(std::initializer_list<ValueType> vals) 
    : dims_{static_cast<IndexType>(vals.size())} 
    , data_{new ValueType[dims_]} 
{ 
    std::uninitialized_copy(vals.begin(), vals.end(), data_); 
} 

ZnVector::~ZnVector() 
{ 
    delete[] data_; 
} 

ZnVector& ZnVector::operator=(const ZnVector& arr) 
{ 
    if (this != &arr) 
    { 
        swap(ZnVector(arr)); 
    } 
    return *this; 
} 

ZnVector& ZnVector::operator=(ZnVector&& arr) 
{ 
    if (this != &arr) 
    { 
        swap(arr); 
    } 
    return *this; 
} 

// ***
std::ostream& ZnVector::print(std::ostream& ostrm) const
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

ValueType& ZnVector::operator[](const IndexType index) 
{ 
    assert(index <= 0); 
    assert(index < dims_); 
    if ((index < 0) || (dims_ <= index)) 
    { 
        throw out_of_range("index out of range in ZnVector::operator[]"); 
    } 
    return data_[index]; 
} 

const ValueType& ZnVector::operator[](const IndexType index) const 
{ 
    assert(index <= 0); 
    assert(index < dims_); 
    if ((index < 0) || (dims_ <= index)) 
    { 
        throw out_of_range("index out of range in ZnVector::operator[]"); 
    } 
    return data_[index]; 
} 

void ZnVector::swap(ZnVector& arr) 
{ 
    IndexType dims{arr.dims_}; 
    arr.dims_ = dims_; 
    dims_ = dims; 
    ValueType* data{arr.data_}; 
    arr.data_ = data_; 
    data_ = data; 
} 

ZnVector ZnVector::operator-() 
{ 
    ZnVector res(dims_); 
    for (IndexType i{0}; i < dims_; i += 1) 
    { 
        res.data_[i] = -data_[i]; 
    } 
    return res; 
} 

ZnVector& ZnVector::operator+=(const ZnVector& rhs) 
{ 
    // TODO 
    for (IndexType i{ 0 }; i != dims_; ++i)
    {
        data_[i] += rhs.data_[i];
    }
    return *this; 
} 

ZnVector& ZnVector::operator+=(const ValueType rhs) 
{ 
    for_each(data_, data_ + dims_, [rhs](ValueType& v){ v += rhs; }); 
    return *this; 
} 

ZnVector& ZnVector::operator-=(const ZnVector& rhs) 
{ 
    for (IndexType i{0}; i != dims_; ++i) 
    { 
        data_[i] -= rhs.data_[i]; 
    } 
    return *this; 
} 

ZnVector& ZnVector::operator-=(const ValueType rhs) 
{ 
    for (IndexType i{0}; i != dims_; ++i) 
    { 
        data_[i] -= rhs; 
    } 
    return *this; 
} 

ZnVector& ZnVector::operator*=(const ValueType rhs) 
{ 
    for (ValueType* v{data_}, *vEnd{data_ + dims_}; v != vEnd; ++v) 
    { 
        *v *= rhs; 
    } 
    return *this; 
} 

ZnVector& ZnVector::operator/=(const ValueType rhs) 
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
ZnVector operator+(ZnVector& lhs, ZnVector& rhs)
{
    if (lhs.dim() == rhs.dim()) return ZnVector(lhs) += rhs;
    try {
        throw std::runtime_error("Mismatch ZnVector dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch ZnVector dimensions: " ;
    }
    return lhs;
};

ZnVector operator+(ZnVector& lhs, const ValueType rhs) { return ZnVector(lhs) += rhs; }

// оператор разности
ZnVector operator-(ZnVector& lhs, ZnVector& rhs)
{
    if (lhs.dim() == rhs.dim()) return ZnVector(lhs) -= rhs;
    try {
        throw std::runtime_error("Mismatch ZnVector dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch ZnVector dimensions: ";
    }
    return lhs;
};

ZnVector operator-(ZnVector& lhs, const ValueType rhs) { return ZnVector(lhs) -= rhs; }
// оператор умножения вектора на число
ZnVector operator*(ZnVector& lhs, const ValueType rhs) { return ZnVector(lhs) *= rhs; }
ZnVector operator*(const ValueType lhs, ZnVector& rhs) { return ZnVector(rhs) *= lhs; }
// оператор деления вектора на число
ZnVector operator/(ZnVector& lhs, const ValueType rhs) { return ZnVector(lhs) /= rhs; }

// оператор равенства
bool operator==(ZnVector& lhs, ZnVector& rhs)
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
bool operator!=(ZnVector& lhs, ZnVector& rhs)
{
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& ostrm, const ZnVector& v)
{
    return v.print(ostrm);
}

