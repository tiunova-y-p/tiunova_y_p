#include "znvectort.h" 

#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace std; 

template<typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType>::ZnVectorT(const IndexType dims)
    : dims_{dims} 
{ 
    data_ = new ValueType[dims_]{0};
} 

template<typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType>::ZnVectorT(const ZnVectorT& vec) 
    : dims_{vec.dims_} 
    , data_{new ValueType[dims_]} 
{ 
    std::uninitialized_copy(vec.data_, vec.data_ + vec.dims_, data_); 
} 

template<typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType>::ZnVectorT(ZnVectorT&& vec) 
    : dims_{vec.dims_} 
    , data_{vec.data_} 
{ 
    vec.dims_ = 0; 
    vec.data_ = nullptr; 
} 

template<typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType>::ZnVectorT(std::initializer_list<ValueType> vals) 
    : dims_{static_cast<IndexType>(vals.size())} 
    , data_{new ValueType[dims_]} 
{ 
    std::uninitialized_copy(vals.begin(), vals.end(), data_); 
} 

template<typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType>::~ZnVectorT() 
{ 
    delete[] data_; 
} 

template<typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>::operator=(const ZnVectorT& arr)
{ 
    if (this != &arr) 
    { 
        swap(ZnVectorT(arr)); 
    } 
    return *this; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>::operator=(ZnVectorT&& arr)
{ 
    if (this != &arr) 
    { 
        swap(arr); 
    } 
    return *this; 
} 

template<typename IndexType, typename ValueType>
std::ostream& ZnVectorT<IndexType, ValueType>::print(std::ostream& ostrm) const
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

template<typename IndexType, typename ValueType>
ValueType& ZnVectorT<IndexType, ValueType>::operator[](const IndexType index) 
{ 
    if ((index < 0) || (dims_ <= index)) 
    { 
        throw out_of_range("index out of range in ZnVectorT<IndexType, ValueType>:: operator[]"); 
    } 
    return data_[index]; 
} 

template<typename IndexType, typename ValueType>
const ValueType& ZnVectorT<IndexType, ValueType>:: operator[](const IndexType index) const 
{ 
    if ((index < 0) || (dims_ <= index)) 
    { 
        throw out_of_range("index out of range in ZnVectorT<IndexType, ValueType>:: operator[]"); 
    } 
    return data_[index]; 
} 

template<typename IndexType, typename ValueType>
void ZnVectorT<IndexType, ValueType>::swap(ZnVectorT& arr) 
{ 
    IndexType dims{arr.dims_}; 
    arr.dims_ = dims_; 
    dims_ = dims; 
    ValueType* data{arr.data_}; 
    arr.data_ = data_; 
    data_ = data; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>:: operator+=(const ZnVectorT& rhs)
{ 
    for (IndexType i{ 0 }; i != dims_; ++i)
    {
        data_[i] += rhs.data_[i];
    }
    return *this; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>:: operator+=(const ValueType rhs)
{ 
    for_each(data_, data_ + dims_, [rhs](ValueType& v){ v += rhs; }); 
    return *this; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>:: operator-=(const ZnVectorT& rhs)
{ 
    for (IndexType i{0}; i != dims_; ++i) 
    { 
        data_[i] -= rhs.data_[i]; 
    } 
    return *this; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>:: operator-=(const ValueType rhs)
{ 
    for (IndexType i{0}; i != dims_; ++i) 
    { 
        data_[i] -= rhs; 
    } 
    return *this; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>:: operator*=(const ValueType rhs)
{ 
    for (ValueType* v{data_}, *vEnd{data_ + dims_}; v != vEnd; ++v) 
    { 
        *v *= rhs; 
    } 
    return *this; 
} 

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType>& ZnVectorT<IndexType, ValueType>:: operator/=(const ValueType rhs)
{ 
    for (ValueType* v{ data_ }, *vEnd{ data_ + dims_ }; v != vEnd; ++v)
    {
        *v /= rhs;
    }
    return *this; 
}

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator+(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs)
{
    if (lhs.dim() == rhs.dim()) return ZnVectorT<IndexType, ValueType>(lhs) += rhs;
    try {
        throw std::runtime_error("Mismatch ZnVectorT dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch ZnVectorT dimensions: " ;
    }
    return lhs;
};

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator+(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs) 
{
    return ZnVectorT<IndexType, ValueType>(lhs) += rhs;
}

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator-(ZnVectorT<IndexType, ValueType>& v)
{
    for (IndexType i{ 0 }; i < v.dim(); i += 1)
    {
        *(v.begin() + i) = -(*(v.begin() + i));
    }
    return v;
}

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator-(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs)
{
    if (lhs.dim() == rhs.dim()) return ZnVectorT<IndexType, ValueType>(lhs) -= rhs;
    try {
        throw std::runtime_error("Mismatch ZnVectorT dimensions");
    }
    catch (const std::runtime_error & e) {
        cout << "Mismatch ZnVectorT dimensions: ";
    }
    return lhs;
};

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator-(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs) 
{ 
    return ZnVectorT<IndexType, ValueType>(lhs) -= rhs; 
}

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator*(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs) 
{ 
    return ZnVectorT<IndexType, ValueType>(lhs) *= rhs;
}

template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator*(const ValueType lhs, ZnVectorT<IndexType, ValueType>& rhs) 
{ 
    return ZnVectorT<IndexType, ValueType>(rhs) *= lhs; 
}
 
template<typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator/(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs) 
{ 
    return ZnVectorT<IndexType, ValueType>(lhs) /= rhs; 
}

template<typename IndexType, typename ValueType>
bool operator==(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs)
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

template<typename IndexType, typename ValueType>
bool operator!=(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs)
{
    return !(lhs == rhs);
}

template<typename IndexType, typename ValueType>
std::ostream& operator<<(std::ostream& ostrm, const ZnVectorT<IndexType, ValueType>& v)
{
    return v.print(ostrm);
}

