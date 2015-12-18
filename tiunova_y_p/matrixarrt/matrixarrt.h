#ifndef MATRIXARRT_H_20151206
#define MATRIXARRT_H_20151206 

#include <initializer_list>
#include <memory>

//упреждающие объ€влени€ внешних операторов  
template <typename IndexType, typename ValueType> class MatrixArrT;

template <typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator+(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator-(MatrixArrT<IndexType, ValueType>& v);

template <typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator-(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
MatrixArrT<IndexType, ValueType>& operator*(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
bool operator==(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
bool operator!=(MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);

template <typename IndexType, typename ValueType>
std::ostream& operator<<(std::ostream& ostrm, const MatrixArrT<IndexType, ValueType>& v);


//шаблон класса matrixarrt
template <typename IndexType, typename ValueType>
class MatrixArrT  
{ 
public: 
    MatrixArrT() = default;
    MatrixArrT(const IndexType rows, const IndexType cols);
    MatrixArrT(const IndexType rows, const IndexType cols, std::initializer_list<ValueType> list);
    MatrixArrT(const MatrixArrT& m) = delete; 
    MatrixArrT(MatrixArrT&& m) = delete; 

    ~MatrixArrT();

    MatrixArrT& operator=(const MatrixArrT& m) = delete; 
    MatrixArrT& operator=(MatrixArrT&& m) = delete; 
    
    IndexType nRows() { return rows_; }
    IndexType nCols() { return cols_; }

    ValueType* begin() { return data_; }
    ValueType* end() { return data_ + rows_*cols_; }

    MatrixArrT& transpose();

    std::ostream& print(std::ostream& ostrm) const;

    MatrixArrT& operator+=(const ValueType rhs); 
    MatrixArrT& operator-=(const ValueType rhs); 
    MatrixArrT& operator*=(const ValueType rhs); 

    ValueType& operator()(const IndexType irow, const IndexType icol);
    const ValueType& operator()(const IndexType irow, const IndexType icol) const;

    friend MatrixArrT<IndexType, ValueType>& operator+ <typename IndexType, typename ValueType> (MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);
    friend MatrixArrT<IndexType, ValueType>& operator- <typename IndexType, typename ValueType> (MatrixArrT<IndexType, ValueType>& v);
    friend MatrixArrT<IndexType, ValueType>& operator- <typename IndexType, typename ValueType> (MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);
    friend MatrixArrT<IndexType, ValueType>& operator* <typename IndexType, typename ValueType> (MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);
    friend bool operator== <typename IndexType, typename ValueType> (MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);
    friend bool operator!= <typename IndexType, typename ValueType> (MatrixArrT<IndexType, ValueType>& lhs, MatrixArrT<IndexType, ValueType>& rhs);
    friend std::ostream& operator<< <typename IndexType, typename ValueType> (std::ostream& ostrm, const MatrixArrT<IndexType, ValueType>& v);


private:
    void MatrixArrT::swap(MatrixArrT& m);

private: 
    IndexType  rows_{ 0 }; 
    IndexType  cols_{ 0 };
    ValueType* data_{nullptr}; 
}; 

#endif //  MATRIXARRT_H_20151206