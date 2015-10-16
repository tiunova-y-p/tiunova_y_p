#ifndef ZNVECTORD_H_20151016
#define ZNVECTORD_H_20151016 

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

#endif // ZNVECTORD_H_20151016