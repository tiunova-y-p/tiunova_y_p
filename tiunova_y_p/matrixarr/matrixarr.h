#ifndef MATRIXARR_H_20151106
#define MATRIXARR_H_20151106 

#include <memory> 

class MatrixArr  
{ 
    using ValueType = int32_t;
    using IndexType = ptrdiff_t;

public: 
    MatrixArr() = default;
    MatrixArr(const IndexType rows, const IndexType cols);
    MatrixArr(const IndexType rows, const IndexType cols, std::initializer_list<ValueType> list);
    MatrixArr(const MatrixArr& m) = delete; 
    MatrixArr(MatrixArr&& m) = delete; 

    ~MatrixArr();

    MatrixArr& operator=(const MatrixArr& m) = delete; 
    MatrixArr& operator=(MatrixArr&& m) = delete; 
    
    IndexType nRows() { return rows_; }
    IndexType nCols() { return cols_; }

    ValueType* begin() { return data_; }
    ValueType* end() { return data_ + rows_*cols_; }

    MatrixArr& transpose();

    std::ostream& print(std::ostream& ostrm) const;

    MatrixArr& operator-();
    MatrixArr& operator+=(const ValueType rhs); 
    MatrixArr& operator-=(const ValueType rhs); 
    MatrixArr& operator*=(const ValueType rhs); 

    ValueType& operator()(const IndexType irow, const IndexType icol);
    const ValueType& operator()(const IndexType irow, const IndexType icol) const;

private:
    void MatrixArr::swap(MatrixArr& m);

private: 
    IndexType  rows_{ 0 }; 
    IndexType  cols_{ 0 };
    ValueType* data_{nullptr}; 
}; 

MatrixArr& operator+(MatrixArr& lhs, MatrixArr& rhs);
MatrixArr& operator-(MatrixArr& lhs, MatrixArr& rhs);
MatrixArr& operator*(MatrixArr& lhs, MatrixArr& rhs);

bool operator==(MatrixArr& lhs, MatrixArr& rhs);
bool operator!=(MatrixArr& lhs, MatrixArr& rhs);

std::ostream& operator<<(std::ostream& ostrm, const MatrixArr& v);

#endif //  MATRIXARR_H_2015110