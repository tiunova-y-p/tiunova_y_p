#ifndef MATRIXNEC_H_20151121
#define MATRIXNEC_H_20151121 

//#include <initializer_list>
#include <memory> 

class MatrixNec
{
    using ValueType = int32_t;
    using IndexType = ptrdiff_t;

public:
    MatrixNec() = default;
    MatrixNec(const IndexType rows, const IndexType cols);
    MatrixNec(const IndexType rows, const IndexType cols, std::initializer_list<ValueType> list);
    MatrixNec(const MatrixNec& m);
    MatrixNec(MatrixNec&& m);

    ~MatrixNec();

    MatrixNec& operator=(const MatrixNec& m);
    MatrixNec& operator=(MatrixNec&& m);

    IndexType nRows() { return rows_; }
    IndexType nCols() { return cols_; }
    ValueType** begin() { return data_; }

    ValueType& operator()(const IndexType irow, const IndexType icol);
    const ValueType& operator()(const IndexType irow, const IndexType icol) const;

    MatrixNec& transpose();

    std::ostream& print(std::ostream& ostrm) const;

    MatrixNec& operator-();
    MatrixNec& operator+=(const ValueType rhs); 
    MatrixNec& operator-=(const ValueType rhs); 
    MatrixNec& operator*=(const ValueType rhs); 

private:
    void MatrixNec::swap(MatrixNec& m);

private:
    IndexType  rows_{ 0 };
    IndexType  cols_{ 0 };
    ValueType** data_{ nullptr };
};

MatrixNec& operator+(MatrixNec& lhs, MatrixNec& rhs);
MatrixNec& operator-(MatrixNec& lhs,MatrixNec& rhs);
MatrixNec& operator*(MatrixNec& lhs,MatrixNec& rhs);

bool operator==(MatrixNec& lhs, MatrixNec& rhs);
bool operator!=(MatrixNec& lhs, MatrixNec& rhs);

std::ostream& operator<<(std::ostream& ostrm, const MatrixNec& m);

#endif // MATRIXNEC_H_2015121





