#ifndef ZNVECTOR_H_20150926
#define ZNVECTOR_H_20150926 

#include <cstddef>
#include <cstdint> 
#include <initializer_list>
#include <memory> 

using ValueType = int32_t;
using IndexType = ptrdiff_t;

class ZnVector 
{ 
public: 
    ZnVector() = default;
    ZnVector(const IndexType dims);
    ZnVector(std::initializer_list<ValueType> list); 
    ZnVector(const ZnVector& vec); 
    ZnVector(ZnVector&& vec); 

    ~ZnVector();

    ZnVector& operator=(const ZnVector& vec); 
    ZnVector& operator=(ZnVector&& vec); 

    // *** 
    IndexType dim() { return dims_; }
    std::ostream& print(std::ostream& ostrm) const;

    ZnVector operator-();
    ZnVector& operator+=(const ZnVector& rhs); 
    ZnVector& operator+=(const ValueType rhs); 
    ZnVector& operator-=(const ZnVector& rhs); 
    ZnVector& operator-=(const ValueType rhs); 
    ZnVector& operator*=(const ValueType rhs); 
    ZnVector& operator/=(const ValueType rhs); 

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
    void swap(ZnVector& arr); 
}; 

// *** 
ZnVector operator+(ZnVector& lhs, ZnVector& rhs);
ZnVector operator+(ZnVector& lhs, const ValueType rhs);
ZnVector operator-(ZnVector& lhs, ZnVector& rhs);
ZnVector operator-(ZnVector& lhs, const ValueType rhs);
ZnVector operator*(ZnVector& lhs, const ValueType rhs);
ZnVector operator*(const ValueType lhs, ZnVector& rhs);
ZnVector operator/(ZnVector& lhs, const ValueType rhs);

bool operator==(ZnVector& lhs, ZnVector& rhs);
bool operator!=(ZnVector& lhs, ZnVector& rhs);

std::ostream& operator<<(std::ostream& ostrm, const ZnVector& v);

#endif // ZNVECTOR_H_20150926


