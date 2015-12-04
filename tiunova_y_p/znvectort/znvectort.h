#ifndef ZNVECTORT_H_20151126
#define ZNVECTORT_H_20151126

#include <initializer_list>
#include <memory> 

//упреждающие объ€влени€ внешних операторов  
template <typename IndexType, typename ValueType> class ZnVectorT;

template <typename IndexType, typename ValueType> 
ZnVectorT<IndexType, ValueType> operator+(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator+(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator-(ZnVectorT<IndexType, ValueType>& v);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator-(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator-(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator*(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator*(const ValueType lhs, ZnVectorT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
ZnVectorT<IndexType, ValueType> operator/(ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);

template <typename IndexType, typename ValueType>
bool operator==(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
bool operator!=(ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
std::ostream& operator<<(std::ostream& ostrm, const ZnVectorT<IndexType, ValueType>& v);

//шаблон класса znvectort
template <typename IndexType, typename ValueType>
class ZnVectorT 
{ 
public: 
    ZnVectorT() = default;
    ZnVectorT(const IndexType dims);
    ZnVectorT(std::initializer_list<ValueType> list); 
    ZnVectorT(const ZnVectorT& vec); 
    ZnVectorT(ZnVectorT&& vec); 

    ~ZnVectorT();

    ZnVectorT& operator=(const ZnVectorT& vec); 
    ZnVectorT& operator=(ZnVectorT&& vec); 

    IndexType dim() { return dims_; }
    std::ostream& print(std::ostream& ostrm) const;

    ZnVectorT& operator+=(const ZnVectorT& rhs); 
    ZnVectorT& operator+=(const ValueType rhs); 
    ZnVectorT& operator-=(const ZnVectorT& rhs); 
    ZnVectorT& operator-=(const ValueType rhs); 
    ZnVectorT& operator*=(const ValueType rhs); 
    ZnVectorT& operator/=(const ValueType rhs); 

    ValueType& operator[](const IndexType index); 
    const ValueType& operator[](const IndexType index) const;

    ValueType* begin() { return data_; } 
    ValueType* end() { return data_ + dims_; } 
    const ValueType* cbegin() { return data_; } 
    const ValueType* cend() { return data_ + dims_; } 

    friend ZnVectorT<IndexType, ValueType> operator+ <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);
    friend ZnVectorT<IndexType, ValueType> operator+ <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);
    friend ZnVectorT<IndexType, ValueType> operator- <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& v);
    friend ZnVectorT<IndexType, ValueType> operator- <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);
    friend ZnVectorT<IndexType, ValueType> operator- <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);
    friend ZnVectorT<IndexType, ValueType> operator* <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);
    friend ZnVectorT<IndexType, ValueType> operator* <typename IndexType, typename ValueType> (const ValueType lhs, ZnVectorT<IndexType, ValueType>& rhs);
    friend ZnVectorT<IndexType, ValueType> operator/ <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, const ValueType rhs);
    friend bool operator== <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);
    friend bool operator!= <typename IndexType, typename ValueType> (ZnVectorT<IndexType, ValueType>& lhs, ZnVectorT<IndexType, ValueType>& rhs);
    friend std::ostream& operator<< <typename IndexType, typename ValueType> (std::ostream& ostrm, const ZnVectorT<IndexType, ValueType>& v);

private:
    void swap(ZnVectorT& arr);

private:
    IndexType  dims_{0}; 
    ValueType* data_{nullptr}; 
}; 

#endif // ZNVECTORT_H_20151126


